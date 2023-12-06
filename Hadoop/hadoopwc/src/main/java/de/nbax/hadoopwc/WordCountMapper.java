package src.main.java.de.nbax.hadoopwc;

import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class WordCountMapper extends Mapper<LongWritable, Text, Text, IntWritable> {
    private final static IntWritable one = new IntWritable(1);
    private Text word = new Text();

    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
    String[] words = value.toString().split("[\\s\\/\\\\,\\.\\-']+");
        for (String w : words) {
            word.set(w);
            context.write(word, one);
        }
    }
}
