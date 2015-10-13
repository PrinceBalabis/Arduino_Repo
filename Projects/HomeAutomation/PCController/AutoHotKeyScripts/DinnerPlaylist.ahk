Process, Exist, Spotify.exe ; check to see if Spotify is runnning
If (ErrorLevel = 0) ; If it is not running
	{
		Run, C:\Users\Prince\AppData\Roaming\Spotify\Spotify.exe, C:\Users\Prince\AppData\Roaming\Spotify, Max
		WinWait, Spotify ;Give Spotify a chance to start before testing
		IfWinExist, Spotify
		{
			sleep, 7000 ; Wait a moment for Spotify to load completly before continuing
			StartChillPlaylist()
		}
	}
Else ; If it is running
	{
	StartChillPlaylist()
	}

StartChillPlaylist()
{
	GiveFocusSpotify()
	send, ^l ;Ctrl-L (Give focus to address/search field )
	sleep, 1
	send, ^a ;CTRL - A (Select text field)
	sleep, 1
	send, {Backspace} ;Backspace (Clear text field)
	sleep, 1
	Send dinner with friends ; Search for Dinner with Friends playlist
	sleep, 2500
	GiveFocusSpotify()
	send, {Down} ;Arrow down (To focus on playlist)
	sleep, 1
	send, {Enter} ;Enter (To choose playlist)
	sleep, 1500
	GiveFocusSpotify()
	send, {Tab} ;Tab (To shift focus to playlist)
	sleep, 1
	send, {Enter} ;Enter (To activate focus to playlist)
	sleep, 1
	Loop 9 ;9x tab (To shift focus to song lists)
	{
		send, {Tab}
		sleep, 1
	}
	Random, rand, 2, 50
	Loop %rand% ; Press down arrow random times to randomize first song!
	{
	send, {Down}
	sleep, 1
	}
	sleep, 1
	send, {Enter}
	msgbox, Spotify Dinner Playlist Started!
}

GiveFocusSpotify()
{
	Run, C:\Users\Prince\AppData\Roaming\Spotify\Spotify.exe, C:\Users\Prince\AppData\Roaming\Spotify, Max
	sleep, 400
}
