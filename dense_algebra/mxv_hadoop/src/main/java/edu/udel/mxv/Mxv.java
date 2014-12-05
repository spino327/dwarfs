package edu.udel.mxv;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class Mxv extends Configured implements Tool {

    static final String USAGE = "hadoop jar path/to/jar n(number of elements in vector x) /path/to/matrix(HDFS) /path/to/vector(HDFS) /path/to/output(HDFS)";
    
    public static void main(String[] args) throws Exception {
        int res = ToolRunner.run(new Configuration(), new Mxv(), args);
        System.exit(res);
    }

    @Override
    public int run(String[] args) throws Exception {
        
        if (args.length != 4) {
            System.err.println(USAGE);
            System.exit(1);
        }
        
        int n = Integer.parseInt(args[0]);
        String input_matrix = args[1];
        String input_vector = args[2];
        String output = args[3];
        
        Configuration conf = getConf();
        conf.set("vector.path", input_vector);
        conf.setInt("vector.n", n);
        
        Job job = new Job(conf);
        job.setJobName("mxv");
        job.setJarByClass(getClass());
        
        // mapper
        job.setMapperClass(MxvMap.class);
        job.setMapOutputKeyClass(IntWritable.class);
        job.setMapOutputValueClass(DoubleWritable.class);
        
        // reducer
        job.setReducerClass(MxvRed.class);
        job.setOutputKeyClass(IntWritable.class);
        job.setOutputValueClass(DoubleWritable.class);
//        job.setNumReduceTasks(num_red);
        
        FileInputFormat.addInputPath(job, new Path(input_matrix));
        FileOutputFormat.setOutputPath(job, new Path(output));
        
        return job.waitForCompletion(true) ? 0 : 1;
    }

}
