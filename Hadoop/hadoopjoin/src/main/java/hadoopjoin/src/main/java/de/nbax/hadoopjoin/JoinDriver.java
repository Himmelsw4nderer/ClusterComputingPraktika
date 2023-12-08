package hadoopjoin.src.main.java.de.nbax.hadoopjoin;

import java.io.IOException;
import java.util.ArrayList;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.MultipleInputs;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class JoinDriver {
    public static class TableMapper
            extends Mapper<Object, Text, Text, Text> {
        public void map(Object key, Text value, Context context)
                throws IOException, InterruptedException {
            String record = value.toString();
            String[] parts = record.split("\\|");
            if (parts.length > 4) {
                context.write(new Text(parts[2]), new Text("A|" + parts[1] + '|' +
                        parts[5]));
            }
        }
    }

    public static class ReduceJoinReducer
            extends Reducer<Text, Text, Text, Text> {
        public void reduce(Text key, Iterable<Text> values, Context context)
                throws IOException, InterruptedException {
            ArrayList<String> prod = new ArrayList<String>();
            ArrayList<String> supp = new ArrayList<String>();
            for (Text t : values) {
                String parts[] = t.toString().split("\\|");
                if (parts[0].equals("A")) {
                    prod.add(parts[1] + '|' + parts[2]);
                } else if (parts[0].equals("B")) {
                    supp.add(parts[1] + '|' + parts[2] + '|' + parts[3]);
                }
            }
            for (String p : prod) {
                for (String s : supp) {
                    context.write(key, new Text(p + "|" + s));
                }
            }
        }
    }

    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "reduce-side join");
        job.setJarByClass(JoinDriver.class);
        job.setReducerClass(ReduceJoinReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);
        MultipleInputs.addInputPath(job, new Path(args[0]), TextInputFormat.class,
                TableMapper.class);
        MultipleInputs.addInputPath(job, new Path(args[1]), TextInputFormat.class,
                TableMapper.class);
        FileOutputFormat.setOutputPath(job, new Path(args[2]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}