import java.util.Scanner;
public class ConsoleGame {
    private final Simulation simulation;
    private final Scanner scanner;
    private boolean running;
    private final int refreshRate = 500; // milliseconds

    public ConsoleGame(int fieldSize, int numFarmers) {
        this.simulation = new Simulation(fieldSize, numFarmers);
        this.scanner = new Scanner(System.in);
        this.running = true;
    }

    public void start() {
        simulation.startSimulation();
        
        // Input handling thread
        Thread inputThread = new Thread(() -> {
            while (running) {
                if (scanner.hasNextLine()) {
                    handleCommand(scanner.nextLine().trim().toLowerCase());
                }
            }
        });
        inputThread.setDaemon(true);
        inputThread.start();

        // Main game loop
        while (running) {
            try {
                Thread.sleep(refreshRate);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }

        cleanup();
    }

    private void handleCommand(String command) {
        try {
            switch (command) {
                case "q":
                case "quit":
                    running = false;
                    break;
                case "s":
                case "save":
                    System.out.print("Enter filename to save: ");
                    String saveFile = scanner.nextLine().trim();
                    simulation.saveState(saveFile);
                    break;
                case "l":
                case "load":
                    System.out.print("Enter filename to load: ");
                    String loadFile = scanner.nextLine().trim();
                    simulation.loadState(loadFile);
                    break;
                case "h":
                case "help":
                    printHelp();
                    break;
                default:
                    System.out.println("Unknown command. Type 'h' for help.");
            }
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    private void printHelp() {
        System.out.println("\nAvailable commands:");
        System.out.println("q or quit - Exit the game");
        System.out.println("s or save - Save current state");
        System.out.println("l or load - Load saved state");
        System.out.println("h or help - Show this help");
    }

    private void cleanup() {
        simulation.stopSimulation();
        scanner.close();
        System.out.println("Game terminated.");
    }

    public static void main(String[] args) {
        System.out.println("Welcome to Carrot Farm Simulation!");
        Scanner setupScanner = new Scanner(System.in);
        
        System.out.print("Enter field size (5-20): ");
        int size = getValidInput(setupScanner, 5, 20);
        
        System.out.print("Enter number of farmers (1-5): ");
        int farmers = getValidInput(setupScanner, 1, 5);

        ConsoleGame game = new ConsoleGame(size, farmers);
        game.start();
    }

    private static int getValidInput(Scanner scanner, int min, int max) {
        while (true) {
            try {
                int value = Integer.parseInt(scanner.nextLine().trim());
                if (value >= min && value <= max) return value;
                System.out.printf("Please enter a number between %d and %d: ", min, max);
            } catch (NumberFormatException e) {
                System.out.print("Please enter a valid number: ");
            }
        }
    }
}