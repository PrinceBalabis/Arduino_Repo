import java.awt.AWTException;
import java.awt.Robot;
import java.awt.event.KeyEvent;
import java.io.IOException;

/**
 * A list of methods to run different computer commands
 * 
 * @author Prince
 *
 */
public class ComputerCommands {

	/**
	 * Enable monitors
	 */
	public void enableMonitors() {
		new Thread(new Runnable() {

			@Override
			public void run() {
				Robot robot;
				try {
					robot = new Robot();

					robot.keyPress(KeyEvent.VK_CAPS_LOCK);
					robot.keyRelease(KeyEvent.VK_CAPS_LOCK);

					robot.keyPress(KeyEvent.VK_CAPS_LOCK);
					robot.keyRelease(KeyEvent.VK_CAPS_LOCK);

				} catch (AWTException e) {
					e.printStackTrace();
				}
			}
		}).start();
	}

	/**
	 * Disable monitors
	 */
	public void disableMonitors() {
		executeComputerExecutable("\"Addons/nircmd.exe\" monitor async_off");
	}

	/**
	 * Start Spotify Chill Playlist
	 */
	
	public void spotifyChillPlaylist() {
		executeComputerExecutable("\"Addons/ChillPlaylist.exe\" ");
	}
	
	/**
	 * Start Spotify Dinner Playlist
	 */
	
	public void spotifyDinnerPlaylist() {
		executeComputerExecutable("\"Addons/DinnerPlaylist.exe\" ");
	}
	
	/**
	 * Start Spotify Workout Playlist
	 */
	
	public void spotifyWorkoutPlaylist() {
		executeComputerExecutable("\"Addons/WorkoutPlaylist.exe\" ");
	}
	
	/**
	 * Method which takes on a link to a local .exe file and runs it in an
	 * isolated thread
	 * 
	 * @param command
	 *            link to .exe file
	 */
	private void executeComputerExecutable(String command) {
		new Thread(new Runnable() {

			@Override
			public void run() {
				try {
					Runtime.getRuntime().exec(command);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}).start();
	}
}
