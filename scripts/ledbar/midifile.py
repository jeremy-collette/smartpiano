from mido import MidiFile

class MidiFile:
	def __init__(self, filename):
		self.midi_file = MidiFile(file_name)

		msg_tracks = []
		for i,track in enumerate(self.midi_file.tracks):
		    total_time = 0
		    for msg in track:
		        total_time += msg.time
		        if (msg.type != "note_on" and msg.type != "note_off"):
		            continue
		        msg_tracks.append((total_time, i))
		self.msg_tracks = sorted(msg_tracks, key=lambda x: x[0])

	def get_next_note()


class MidiMessage:
	def __init__(self, key, )	