/*  
 * Copyright (C) 2014 Computer Architecture and Parallel Systems Laboratory (CAPSL) 
 *
 * Original author: Sergio Pino 
 * E-Mail: sergiop@udel.edu
 *
 * License
 *  
 * Redistribution of this code is allowed only after an explicit permission is
 * given by the original author or CAPSL and this license should be included in
 * all files, either existing or new ones. Modifying the code is allowed, but
 * the original author and/or CAPSL must be notified about these modifications.
 * The original author and/or CAPSL is also allowed to use these modifications
 * and publicly report results that include them. Appropriate acknowledgments
 * to everyone who made the modifications will be added in this case.
 *
 * Warranty 
 *
 * THIS CODE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES THAT
 * THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR
 * PURPOSE OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE
 * OF THE COVERED CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN
 * ANY RESPECT, YOU (NOT THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME
 * THE COST OF ANY NECESSARY SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER
 * OF WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS LICENSE. NO USE OF ANY
 * COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER THIS DISCLAIMER.
 */

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

/**
 * 
 * Mapreduce implementation for matrix vector multiplication
 * 
 * @author Sergio Pino sergiop@udel.edu
 */
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
