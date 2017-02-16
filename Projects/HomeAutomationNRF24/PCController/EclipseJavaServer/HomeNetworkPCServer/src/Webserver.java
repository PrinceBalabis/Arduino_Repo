
/**
 * Webserver which listens to commands from HomeNetwork and passes it to 
 * 
 * How to Send a GET HTTP Request from a simple internet browser:
 * http://localhost:5060/1
 * 
 * @author Prince
 *
 */

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class WebServer {
	
	public static void main(String[] args) {
		try {
			HttpServer server = HttpServer.create(new InetSocketAddress(5060), 0);
	        server.createContext("/1", new DisableMonitor());
	        server.createContext("/2", new EnableMonitor());
	        server.createContext("/3", new SpotifyChillPlaylist());
	        server.createContext("/4", new SpotifyDinnerPlaylist());
	        server.createContext("/5", new SpotifyWorkoutPlaylist());
	        server.createContext("/6", new SpotifyWorkPlaylist());
	        server.setExecutor(null); // creates a default executor
	        server.start();
        	System.out.println("Started Webserver");
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		while(true){ // Never end this server software
			try {
				Thread.sleep(Long.MAX_VALUE);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
    }

    /**
     * Disable Monitor
     * @author Prince
     *
     */
    static class DisableMonitor implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
        	sendResponse(t, "Disabled Monitors");
        	System.out.println("Disabled Monitors");
        	new ComputerCommands().disableMonitors();
        }
    }

    /**
     * Enable Monitor
     * @author Prince
     *
     */
    static class EnableMonitor implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
        	sendResponse(t, "Enabled Monitors");
        	System.out.println("Enabled Monitors");
        	new ComputerCommands().enableMonitors();
        }
    }
    
    /**
     * Start Spotify Chill playlist
     * @author Prince
     *
     */
    static class SpotifyChillPlaylist implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
        	sendResponse(t, "Started Spotify Chill playlist");
        	System.out.println("Started Spotify Chill playlist");
        	new ComputerCommands().spotifyChillPlaylist();
        }
    }
    
    /**
     * Start Spotify Dinner playlist
     * @author Prince
     *
     */
    static class SpotifyDinnerPlaylist implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
        	sendResponse(t, "Started Spotify Dinner playlist");
        	System.out.println("Started Spotify Dinner playlist");
        	new ComputerCommands().spotifyDinnerPlaylist();;
        }
    }
    
    /**
     * Start Spotify Workout playlist
     * @author Prince
     *
     */
    static class SpotifyWorkoutPlaylist implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
        	sendResponse(t, "Started Spotify Workout playlist");
        	System.out.println("Started Spotify Workout playlist");
        	new ComputerCommands().spotifyWorkoutPlaylist();;;
        }
    }
    
    /**
     * Start Spotify Work playlist
     * @author Prince
     *
     */
    static class SpotifyWorkPlaylist implements HttpHandler {
        @Override
        public void handle(HttpExchange t) throws IOException {
        	sendResponse(t, "Started Spotify Work playlist");
        	System.out.println("Started Spotify Work playlist");
        	new ComputerCommands().spotifyWorkPlaylist();;;
        }
    }
    
    /**
     * Send a response back to webclient
     * @param t
     * @param response
     * @throws IOException
     */
    private static void sendResponse(HttpExchange t, String response) throws IOException{
        t.sendResponseHeaders(200, response.length());
        OutputStream os = t.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
    
}