package hadoopjoin.src.main.java.de.nbax.hadoopjoin;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.input.MultipleInputs;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class JoinDriver {
    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "reduce-side join");
        job.setJarByClass(JoinDriver.class);
        job.setReducerClass(JoinReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);

        // Input paths for tableA.csv and tableB.csv
        MultipleInputs.addInputPath(job, new Path(args[0]), TextInputFormat.class, JoinMapperA.class);
        MultipleInputs.addInputPath(job, new Path(args[1]), TextInputFormat.class, JoinMapperB.class);
        FileOutputFormat.setOutputPath(job, new Path(args[2]));

        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }

}
