import mido


class MidiFile:
    def __init__(self, filename):
        self.message_index = 0
        midi_file = mido.MidiFile(filename)

        # Pre-process message tracks
        msg_tracks = []
        for i, track in enumerate(midi_file.tracks):
            total_time = 0
            for msg in track:
                total_time += msg.time
                if msg.type != "note_on" and msg.type != "note_off":
                    continue
                msg_tracks.append((total_time, i))
        msg_tracks = sorted(msg_tracks, key=lambda x: x[0])

        # Pre-process messages with track
        messages = []
        i = 0
        for msg in midi_file:
            if msg.type != "note_on" and msg.type != "note_off":
                continue
            on = msg.type == "note_on" and msg.velocity != 0
            track = msg_tracks[i][1]
            i += 1
            messages.append(MidiNote(msg.time, msg.note, on, track))
        self.messages = messages

    def get_next_note(self):
        if self.is_eof():
            return None

        next_note = self.messages[self.message_index]
        self.message_index += 1
        return next_note

    def is_eof(self):
        return self.message_index >= len(self.messages)


class MidiNote:
    def __init__(self, time, note, on, track):
        self.time = time
        self.note = note
        self.on = on
        self.track = track
