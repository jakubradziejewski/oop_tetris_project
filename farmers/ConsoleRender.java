import java.util.Map;
import java.util.HashMap;
public class ConsoleRender {
    private final Grid grid;
    private static final String ANSI_RESET = "\u001B[0m";
    private static final String ANSI_GREEN = "\u001B[32m";
    private static final String ANSI_YELLOW = "\u001B[33m";
    private static final String ANSI_RED = "\u001B[31m";
    private static final String ANSI_BLUE = "\u001B[34m";
    private static final String ANSI_WHITE = "\u001B[37m";

    public ConsoleRender(Grid grid) {
        this.grid = grid;
    }

    public void render() {
        clearScreen();
        int size = grid.getSize();
        StringBuilder sb = new StringBuilder();

        // Create a map of entity positions
        Map<String, Character> entityMap = new HashMap<>();
        for (Entity entity : grid.getEntities()) {
            int[] pos = entity.getPosition();
            String key = pos[0] + "," + pos[1];
            if (entity instanceof Farmer) {
                entityMap.put(key, 'F');
            } else if (entity instanceof Dog) {
                entityMap.put(key, 'D');
            } else if (entity instanceof Rabbit && entity.isActive()) {
                entityMap.put(key, 'R');
            }
        }

        // Render the field
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                String key = x + "," + y;
                if (entityMap.containsKey(key)) {
                    char entity = entityMap.get(key);
                    switch (entity) {
                        case 'F':
                            sb.append(ANSI_BLUE).append('F').append(ANSI_RESET);
                            break;
                        case 'D':
                            sb.append(ANSI_WHITE).append('D').append(ANSI_RESET);
                            break;
                        case 'R':
                            sb.append(ANSI_RED).append('R').append(ANSI_RESET);
                            break;
                    }
                } else {
                    Cell cell = grid.getCell(x, y);
                    switch (cell.getState()) {
                        case EMPTY:
                            sb.append('.');
                            break;
                        case GROWING:
                            sb.append(ANSI_GREEN).append(cell.getGrowthStage())
                              .append(ANSI_RESET);
                            break;
                        case READY:
                            sb.append(ANSI_YELLOW).append('C').append(ANSI_RESET);
                            break;
                        case DAMAGED:
                            sb.append(ANSI_RED).append('X').append(ANSI_RESET);
                            break;
                    }
                }
                sb.append(' ');
            }
            sb.append('\n');
        }
        System.out.println(sb);
    }

    private void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }
}