
import java.util.Random;
import java.util.List;
import java.util.ArrayList;
import java.io.*;
public class Simulation {
    private final Grid grid;
    private final List<Thread> entityThreads;
    private final List<Entity> entities;
    private volatile boolean running;
    private final Random random;
    private final ConsoleRender render;

    public Simulation(int fieldSize, int numFarmers) {
        this.grid = new Grid(fieldSize);
        this.entityThreads = new ArrayList<>();
        this.entities = new ArrayList<>();
        this.random = new Random();
        this.render = new ConsoleRender(grid);
        
        // Initialize farmers
        for (int i = 0; i < numFarmers; i++) {
            Farmer farmer = new Farmer(
                random.nextInt(fieldSize),
                random.nextInt(fieldSize),
                grid
            );
            entities.add(farmer);
            grid.addEntity(farmer);
        }
    }

    public void startSimulation() {
        running = true;
        
        // Start entity threads
        for (Entity entity : entities) {
            Thread thread = new Thread(entity);
            entityThreads.add(thread);
            thread.start();
        }

        // Rabbit spawning and rendering thread
        new Thread(() -> {
            while (running) {
                try {
                    Thread.sleep(5000);
                    spawnRabbit();
                    grid.updateGrowth();
                    render.render();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
        }).start();
    }

    private void spawnRabbit() {
        if (random.nextDouble() < 0.3) { // 30% chance to spawn a rabbit
            Rabbit rabbit = new Rabbit(
                random.nextInt(grid.getSize()),
                random.nextInt(grid.getSize()),
                grid
            );
            grid.addEntity(rabbit);
            Thread rabbitThread = new Thread(rabbit);
            entityThreads.add(rabbitThread);
            rabbitThread.start();
        }
    }

    public void stopSimulation() {
        running = false;
        for (Entity entity : entities) {
            entity.stopRunning();
        }
        for (Thread thread : entityThreads) {
            thread.interrupt();
        }
    }

    public void saveState(String filename) {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) {
            oos.writeObject(grid);
            System.out.println("Game state saved successfully.");
        } catch (IOException e) {
            System.err.println("Failed to save game state: " + e.getMessage());
        }
    }

    public void loadState(String filename) {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filename))) {
            Grid loadedField = (Grid) ois.readObject();
            // Update field state
            System.out.println("Game state loaded successfully.");
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Failed to load game state: " + e.getMessage());
        }
    }
}