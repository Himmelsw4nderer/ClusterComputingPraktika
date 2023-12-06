package hadoopjoin.src.main.java.de.nbax.hadoopjoin;

import java.io.IOException;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class JoinMapper extends Mapper<LongWritable, Text, Text, Text>{
    public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        String[] tokens = value.toString().split("\\|");
        int joinindex = tokens.length > 10 ? 2 : 0;
        String joinprefix = tokens.length > 10 ? "A" : "B";
        System.out.println("Mapper Output: Key=" + tokens[joinindex] + ", Value=" + joinprefix + "|" + value.toString());
        context.write(new Text(tokens[joinindex]), new Text(joinprefix + "|" + value.toString()));
    }
}
