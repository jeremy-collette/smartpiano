from ledbarfactory import LedBarFactory

if (__name__ == "__main__"):
    #filename = "../beethoven_ode_to_joy_tracks.mid"
    filename = "../mgs-jez.mid"
    #filename = "../Sweden_Minecraft.mid"
    #filename = "../happy_birthday_tracks.mid"
    
    led_bar_factory = LedBarFactory()
    piano_led_bar = led_bar_factory.create_led_bar_piano_client(filename)
    piano_led_bar.play()