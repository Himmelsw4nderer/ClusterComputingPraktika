package hadoopjoin.src.main.java.de.nbax.hadoopjoin;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class JoinReducer extends Reducer<Text, Text, Text, Text> {
    public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
        List<String> tableAValues = new ArrayList<>();
        List<String> tableBValues = new ArrayList<>();

        System.out.println("Reducer Input: Key=" + key.toString());

        for (Text value : values) {
            String[] tokens = value.toString().split("\\|");
            if (tokens[0].equals("A")) {
                tableAValues.add(value.toString());
            } else if (tokens[0].equals("B")) {
                tableBValues.add(value.toString());
            }
        }

        for (Text value : values) {
            context.write(key, value);
        }

        // Perform the natural join
        for (String a : tableAValues) {
            for (String b : tableBValues) {
                //context.write(key, new Text(a + "|" + b));
            }
        }
    }
}
