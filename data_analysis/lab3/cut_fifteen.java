import java.util.*;

/**
 * @author Nucleotide
 */
class Board {
    public int[][] blocks; //   Наше поле. пустое место будем обозначать нулем.
    private int zeroX;    // это нам пригодится в будущем - координаты нуля
    private int zeroY;
    private int h; //  мера

    public Board(int[][] blocks) {
        int[][] blocks2 = deepCopy(blocks);   //   копируем, так как нам нужно быть уверенными в неизменяемости
        this.blocks = blocks2;

        h = 0;
        for (int i = 0; i < blocks.length; i++) {  //  в этом цикле определяем координаты нуля и вычисляем h(x)
            for (int j = 0; j < blocks[i].length; j++) {
                if (blocks[i][j] != (i*dimension() + j + 1) && blocks[i][j] != 0) {  // если 0 не на своем месте - не считается
                    h += 1;
                }
                if (blocks[i][j] == 0) {
                    zeroX = (int) i;
                    zeroY = (int) j;
                }
            }
        }
    }


    public int dimension() {
        return blocks.length;
    }

    public int h() {
        return h;
    }

    public boolean isGoal() {  //   если все на своем месте, значит это искомая позиция
        return h == 0;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Board board = (Board) o;

        if (board.dimension() != dimension()) return false;
        for (int i = 0; i < blocks.length; i++) {
            for (int j = 0; j < blocks[i].length; j++) {
                if (blocks[i][j] != board.blocks[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    public Iterable<Board> neighbors() {  // все соседние позиции
        // меняем ноль с соседней клеткой, то есть всего 4 варианта
        // если соседнего нет (0 может быть с краю), chng(...) вернет null
        Set<Board> boardList = new HashSet<Board>();
        boardList.add(chng(getNewBlock(), zeroX, zeroY, zeroX, zeroY + 1));
        boardList.add(chng(getNewBlock(), zeroX, zeroY, zeroX, zeroY - 1));
        boardList.add(chng(getNewBlock(), zeroX, zeroY, zeroX - 1, zeroY));
        boardList.add(chng(getNewBlock(), zeroX, zeroY, zeroX + 1, zeroY));

        return boardList;
    }

    private int[][] getNewBlock() { //  опять же, для неизменяемости
        return deepCopy(blocks);
    }

    private Board chng(int[][] blocks2, int x1, int y1, int x2, int y2) {  //  в этом методе меняем два соседних поля

        if (x2 > -1 && x2 < dimension() && y2 > -1 && y2 < dimension()) {
            int t = blocks2[x2][y2];
            blocks2[x2][y2] = blocks2[x1][y1];
            blocks2[x1][y1] = t;
            return new Board(blocks2);
        } else
            return null;

    }


    public String toString() {
        StringBuilder s = new StringBuilder();
        for (int i = 0; i < blocks.length; i++) {
            for (int j = 0; j < blocks.length; j++) {
                s.append(String.format("%2d ", blocks[i][j]));
            }
            s.append("\n");
        }
        return s.toString();
    }

    private static int[][] deepCopy(int[][] original) {
        if (original == null) {
            return null;
        }

        final int[][] result = new int[original.length][];
        for (int i = 0; i < original.length; i++) {
            result[i] = new int[original[i].length];
            for (int j = 0; j < original[i].length; j++) {
                result[i][j] = original[i][j];
            }
        }
        return result;
    }
}

class Solver {  //  наш "решатель"

    private Board initial;    //
    private List<Board> result = new ArrayList<Board>();   // этот лист - цепочка ходов, приводящих к решению задачи

    private class ITEM{    // Чтобы узнать длину пути, нам нужно помнить предидущие позиции (и не только поэтому)
        private ITEM prevBoard;  // ссылка на предыдущий
        private Board board;   // сама позиция

        private ITEM(ITEM prevBoard, Board board) {
            this.prevBoard = prevBoard;
            this.board = board;
        }

        public Board getBoard() {
            return board;
        }


    }

    public Solver(Board initial) {
        this.initial = initial;

        if(!isSolvable()) return;  //  сначала можно проверить, а решаема ли задача?

        //  очередь. Для нахождения приоритетного сравниваем меры
        PriorityQueue<ITEM> priorityQueue = new PriorityQueue<ITEM>(10, new Comparator<ITEM>() {
            @Override
            public int compare(ITEM o1, ITEM o2) {
                return new Integer(measure(o1)).compareTo(new Integer(measure(o2)));
            }
        });


        // шаг 1
        priorityQueue.add(new ITEM(null, initial));

        while (true){
            ITEM board = priorityQueue.poll(); //  шаг 2

            //   если дошли до решения, сохраняем весь путь ходов в лист
            if(board.board.isGoal()) {
                itemToList(new ITEM(board, board.board));
                return;
            }

            //   шаг 3
            Iterator iterator = board.board.neighbors().iterator(); // соседи
            while (iterator.hasNext()){
                Board board1 = (Board) iterator.next();

                //оптимизация. Очевидно, что один из соседей - это позиция
                // которая была ходом раньше. Чтобы не возвращаться в состояния,
                // которые уже были делаем проверку. Экономим время и память.
                if(board1!= null && !containsInPath(board, board1))
                    priorityQueue.add(new ITEM(board, board1));
            }

        }
    }

    //  вычисляем f(x)
    private static int measure(ITEM item){
        ITEM item2 = item;
        int c= 0;   // g(x)
        int measure = item.getBoard().h();  // h(x)
        while (true){
            c++;
            item2 = item2.prevBoard;
            if(item2 == null) {
                // g(x) + h(x)
                return measure + c;
            }
        }
    }

    //  сохранение
    private void itemToList(ITEM item){
        ITEM item2 = item;
        while (true){
            item2 = item2.prevBoard;
            if(item2 == null) {
                Collections.reverse(result);
                return;
            }
            result.add(item2.board);
        }
    }

    // была ли уже такая позиция в пути
    private boolean containsInPath(ITEM item, Board board){
      ITEM item2 = item;
       while (true){
           if(item2.board.equals(board)) return true;
           item2 = item2.prevBoard;
           if(item2 == null) return false;
       }
    }


    public boolean isSolvable() {
       int [][] blocks = initial.blocks;
       int u = 0, sum = 0;
       int pool_len = 0;
       int i = 0;
       ArrayList<Integer> pool = new ArrayList<Integer>();
       for (int [] y: blocks){
           i = 0;
           for (int t: y){
               if (t == 0){
                   sum += u;
                   sum += 1;
               }
               else{
                   sum += countOfLesserNumbers(u, i, blocks);
               }
               i += 1;
           }
           u += 1;
       }
       return ((sum % 2)==0);
    }
    static public int countOfLesserNumbers(int u, int i, int[][]blocks){
        int t = blocks[u][i];
        int j = 0;
        i+=1; int sum = 0;
        while (u < blocks.length){
            while (i < blocks[u].length){
                j = blocks[u][i];
                if ((j < t) & (j != 0)){
                    sum += 1;
                }
                i += 1;
            }
            u += 1;
        }
        return sum;
    }
    public int moves() { 
        if(!isSolvable()) return -1;
        return result.size() - 1;
    }


    // все ради этого метода - чтобы вернуть result
    public Iterable<Board> solution() {
        return result;
    }
}

public class cut_fifteen{
    public static void main(String [] args){
        int[][] blocks = new int[][]{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {15, 13, 14, 0}};
        Board initial = new Board(blocks);
        Solver solver = new Solver(initial);
        System.out.println("Minimum number of moves = " + solver.moves());
        for (Board board : solver.solution()) System.out.println(board);
    }
}
