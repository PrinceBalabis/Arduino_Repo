import java.io.IOException;

/**
 * A list of methods to run different computer commands
 * 
 * @author Prince
 *
 */
public class ComputerCommands {
	
	/**
	 * Constructor
	 */
	public ComputerCommands() {
	}

	/**
	 * Disable monitors
	 */
	public void disableMonitors() {
		executeComputerExecutable("\"NirCmd/nircmd.exe\" monitor async_off");
	}

	/**
	 * Method which takes on a link to a local .exe file and runs it in an isolated thread
	 * 
	 * @param command
	 *            link to .exe file
	 */
	private void executeComputerExecutable(String command) {
		new Thread(new Runnable(){

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
