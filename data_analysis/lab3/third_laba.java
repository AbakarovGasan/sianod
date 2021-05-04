import static java.lang.System.out;
import java.util.*;

public class third_laba{
    //функция prefix_str возвращает массив длин префиксов строк
    static int [] prefix_str(byte [] str){
        int len = str.length;
        int [] lps = new int[len];
        int i = 1;
        int k;
        while (i < len){
            //найти, какой префикс-суффикс можно расширить
            k = lps[i - 1];
            while ((k > 0)&(str[k] != str[i])){
                k = lps[k - 1];
            }
            //расширить префикс
            if (str[k] == str[i]){
                k += 1;
            }
            lps[i] = k;
            i += 1;
        }
        return lps;
    }
    
    static int kmp(String pat, String txt){
        return kmp(pat, txt, 0);
    }
    
    static int kmp(String pat, String txt, int index){
        return kmp(pat.getBytes(), txt.getBytes(), index);
    }
    
    static int kmp(byte []  pat, byte [] txt, int index){
        int M = pat.length;
        int N = txt.length;
        
        if ((M + 1) > N) return -1; 
        int [] lps = prefix_str(pat);
        int i = index;
        int j = 0;
        while (i < N){
            if (pat[j] == txt[i]){
                j ++;
                i ++;
            }
            if (j == M){
                return i - j;
            }
            else{
                if ((i < N) && (pat[j] != txt[i])){
                    if (j != 0){
                        j = lps[j-1];
                    }
                    else{
                        i += 1;
                    }
                }
            }
        }
        return -1;
    }
    
    static int [] bad_table(byte [] str){
        int [] map = new int [256];
        int L = str.length;
        if (L == 0) return map;
        int i = 0;
        L -= 1;
        while (i < L){
            map[(int)str[i] & 0xFF] = (L - i);
            i += 1;
        }
        L += 1;
        map[(int)str[i] & 0xFF] = (L);
        return map;
    }
    
    static int bmh(String pat, String txt){
        return bmh(pat, txt, 0);
    }
    
    static int bmh(String pat, String txt, int index){
        return bmh(pat.getBytes(), txt.getBytes(), index);
    }
    
    static int bmh(byte [] pat, byte [] txt, int index){
        int M = pat.length;
        int N = txt.length;
        if ((M + index) > N) return -1;
        
        int [] bt = bad_table(pat);
        
        int i = M + index - 1;
        int r = M - 1;
        int f;
        int u = i;
        
        while (u < N){
            while (r >= 0){
                if (pat[r] != txt[u]){
                    break;
                }
                r -= 1;
                u -= 1;
            }
            if (r == -1){
                return i - M + 1;
            }
            f = bt[(int)txt[i] & 0xFF];
            if (f == 0){
                i += r;
                i += 1;
            }
            else{
                i += (int)f;
            }
            u = i;
            r = M - 1;
        }
        return -1; 
    }
    
    static void show_result(String name, int index, long time){
        out.println(name);
        out.println("Время выполнения: "+time+"ns");
        out.println("Результат: "+ index);
    }
    
    static void task2(){
        int n = input.nextInt();
        if ((n % 3) == 0) out.println(3);
        else if ((n % 4) == 0) out.println(4);
        else{
            int i = 5;
            int c = (int)Math.pow(n, 0.5);
            while (((n % i) != 0) & (i <= c)){
                i += 2;
            }
            if (i <= c){
                out.println(i);
            }
            else{
                out.println(n);
            }
        }
    }
    
    static void task3(){
        String s = input.next();
        int l = s.length();
        int i = (int)s.charAt(l - 1);
        i -= (int) '0';
        if (l == 1){
            if (i <= 3){
                out.println("-1");
            }
            else if (i % 2 == 0){
                out.println("10 2");
            }
            else{
                out.println("-1");
            }
        }
        else if (i % 2 == 0){
            out.println("10 2");
        }
        else if (i == 5){
            out.println("10 5");
        }
        else if (i == 3 & i == 9){
            out.println("12 3");
        }
        else if (i == 7){
            out.println("14 7");
        }
        else{
            int j = 0;
            for (char z: s.toCharArray()){
                j += (int) z;
                j -= (int) '0';
            }
            out.println(j + 1 + " " + j);
        }
    }
    
    static void task1(){
        boolean result = true;
        String command;
        String part;
        char part1;
        int temp;
        int i = input.nextInt();
        ArrayList <Character> s = new ArrayList<Character>(i);
        while (i > 0){
            i -= 1;
            command = input.next().toLowerCase();
            part = input.next().toLowerCase();
            if (part.length() != 1){
                throw new java.util.InputMismatchException();
            }
            part1 = part.charAt(0);
            if (part1 < 'a' || part1 > 'z'){
                throw new java.util.InputMismatchException();
            }
            if (command.equals("vote")){
                if (result){
                    temp = s.size();
                    if (temp == 0) result = false;
                    else{
                        temp -= 1;
                        if (s.get(temp) == part1){
                            s.remove(temp);
                        }
                        else result = false;
                    }
                }
            }
            else if (command.equals("add")){
                if (result){
                    s.add(part1);
                }
            }
            else{
                throw new java.util.InputMismatchException();
            }
        }
        if (s.size() != 0){
            result = false;
        }
        out.println(result?"Yes":"No");
    }
    
    static Scanner input = new Scanner(System.in);
    
    static void main1(){
        String pattern, source;
        
        int index;
        
        out.print("Введите строку: ");
        source = input.nextLine();
        out.print("Введите подстроку: ");
        pattern = input.nextLine();
        
        long time;
        
        time = System.nanoTime();
        index = kmp(pattern, source);
        time = System.nanoTime() - time;
        show_result("поиск методом Кнута-Морриса-Пратта", index, time);
        
        time = System.nanoTime();
        index = bmh(pattern, source);
        time = System.nanoTime() - time;
        show_result("поиск методом Бойера — Мура — Хорспула", index, time);
        
    }
    
    static void main2(){
        ArrayList<Integer> board_list = new ArrayList<Integer>(16);
        int k;
        for (int i = 0; i < 16; i ++){
            k = (input.nextInt());
            if (k > 15) throw new java.util.InputMismatchException();
            if (board_list.contains(k)) throw new java.util.InputMismatchException();
            board_list.add(k);
        }
        Board board = new Board(board_list);
        board = board.AStar();
        for (int i: board.full_trace()){
            out.print(i+ " ");
        }
    }
    
    static public void main(String [] args){  
        task3();
    }
} 

class Board implements Comparable<Board>{
    public List<Integer> board_list;
    public Board previous;
    public int trace;
    public int g;
    public int h;
    public int f;
    public List<Integer> trace_path = null;
    
    public static Board AStar(Board initial){
        if (initial.is_solvable()){
            PriorityQueue<Board> queue = new PriorityQueue<Board>();
            Set<Board> set = new HashSet<>();
            queue.add(initial);
            Board t;
            Board [] array;
            while (true){
                t = queue.poll();
                set.add(t);
                if (t.h == 0) return t;
                array = t.neighbours();
                for (Board i: array){
                    if (i == null){
                        continue;
                    }
                    else if (set.contains(i)){
                        continue;
                    }
                    else{
                        queue.add(i);
                    }
                }
            }
        }
        else{
            return null;
        }
    }
    public Board AStar(){
        return AStar(this);
    }
    public int hashCode(){
        return board_list.hashCode();
    }
    public int compareTo(Board other){
        int u = Integer.compare(this.f, other.f);
        if (u == 0){
            return Integer.compare(this.g, other.g);
        } 
        else{
            return u;
        }
    }
    public boolean equals(Object other){
        if (other instanceof Board){
            return equals((Board)other);
        }
        return false;
    }
    public boolean equals(Board other){
        return this.board_list.equals(other.board_list);
    }
    public String toString(){
        String fmt = "%3d";
        int t = 0;
        StringBuilder out = new StringBuilder();
        out.append("\n");
        for (int i = 0; i < 16; i++){
            t += 1;
            out.append(String.format(fmt, board_list.get(i)));
            if (t == 4){
                out.append("\n");
                t = 0;
            }
        }
        out.append(" h: ");
        out.append(Integer.toString(this.h));
        out.append(" g: ");
        out.append(Integer.toString(this.g));
        out.append(" f: ");
        out.append(Integer.toString(this.f));
        out.append("\n");
        return out.toString();
    }
    public Board(List<Integer> v){
        this(v, null, 0);
    }
    public Board(List<Integer> v, Board prev, int trace){
        this.board_list = v;
        this.previous = prev;
        this.trace = trace;
        int i = 0;
        int u;
        this.h = 0;
        while (i < 16){
            u = v.get(i);
            i += 1;
            if ((!(u == 0))&&(!(u == i))){
                this.h += 1;
            }
        }
        if (prev == null){
            this.g = 0;
            this.f = h;
        }
        else{
            this.g = prev.g + 1;
            this.f = this.g + this.h;
        }
    }
    public List<Integer> full_trace(){
        if (this.trace_path == null){ 
            Integer [] array = new Integer[this.g];
            int i = this.g;
            Board t = this;
            while (i > 0){
                i -= 1;
                array[i] = (t.trace);
                t = t.previous;
            }
            this.trace_path = Collections.unmodifiableList(
            new ArrayList<Integer>(Arrays.asList(array)));
        }
        return this.trace_path;
    }
    public boolean is_solvable(){
        int i = 0;
        int s = 0;
        int u = 0;
        int t = 0;
        int c = 0;
        while (i < 16){
            u = this.board_list.get(i);
            if (u == 0){
                s += i / 16;
                s += 1;
            }
            else{
                t = i + 1;
                while (t < 16){
                    c = this.board_list.get(t);
                    t += 1;
                    if (u > c){
                        s += 1;
                    }
                }
            }
            i += 1;
        }
        return (s % 2) == 0;
    }
    public Board[] neighbours(){
        int i = board_list.indexOf(0);
        Board [] bb = new Board[4];
        int a, b, c;
        List<Integer> j;
        c = i + 4; 
        if ((c) < 16){
            j = new ArrayList<Integer>(board_list);
            a = j.get(i);
            b = j.get(c);
            j.set(i, b);
            j.set(c, 0);
            bb[0] = (new Board(j, this, b));
        }
        c = i - 4;
        if ((c) >= 0){
            j = new ArrayList<Integer>(board_list);
            a = j.get(i);
            b = j.get(c);
            j.set(i, b);
            j.set(c, 0);
            bb[1] = (new Board(j, this, b));
        }
        c = i + 1;
        if ((i % 4) + 1 < 4 && c < 16){
            j = new ArrayList<Integer>(board_list);
            a = j.get(i);
            b = j.get(c);
            j.set(i, b);
            j.set(c, 0);
            bb[2] = (new Board(j, this, b));
        }
        c = i - 1;
        if ((i % 4) - 1 >= 0 && c >= 0){
            j = new ArrayList<Integer>(board_list);
            a = j.get(i);
            b = j.get(c);
            j.set(i, b);
            j.set(c, 0);
            bb[3] = (new Board(j, this, b));
        }
        return bb;
    }
}

