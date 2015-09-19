/**
 * Class which runs at program start and launches webserver.
 * Gets commands from webserver and runs the appropiate computer command
 * @author Prince
 *
 */
public class MainBrain {
	static ComputerCommands computerCommands = new ComputerCommands();
	
	public static void main(String[] args) {
		computerCommands.disableMonitors();
	}
}
