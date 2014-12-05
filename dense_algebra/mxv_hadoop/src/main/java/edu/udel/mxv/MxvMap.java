package edu.udel.mxv;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.IOException;
import java.net.URI;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

/**
 * Performs the multiplication between the aij and the xi
 * 
 * The vector x is loaded in each map task in the setup method. Here it is assume that the size of 
 * the vector x can fit in the mapper memory.
 * 
 * Each mapper loads the vector.
 */
public class MxvMap extends Mapper<LongWritable, Text, IntWritable, DoubleWritable>{

    private static final Log LOG = LogFactory.getLog(MxvMap.class);
    private double[] x_i;

    private final IntWritable row = new IntWritable();
    private final DoubleWritable aij_x_vj = new DoubleWritable();
    
    @Override
    protected void setup(
            Mapper<LongWritable, Text, IntWritable, DoubleWritable>.Context context)
            throws IOException, InterruptedException {
        
        Configuration conf = context.getConfiguration();
        
        String input_vector = conf.get("vector.path");
        x_i = new double[conf.getInt("vector.n", 0)];
        
        FileSystem fs = FileSystem.get(URI.create(input_vector), conf);
        FileStatus[] status = fs.listStatus(new Path(input_vector));
        for (int i=0; i<status.length; ++i) {
            Path file = status[i].getPath();
            System.out.println("status: " + i + " " + file.toString());
            
            DataInputStream dis = new DataInputStream(fs.open(file));
            
            String line = null;
            int count = 0;
            while ((line = dis.readLine()) != null) {
                String[] split_line = line.split(",");
                if (split_line.length == 2) {
                    int pos = Integer.parseInt(split_line[0]);
                    double val = Double.parseDouble(split_line[1]);
                    x_i[pos++] = val;
                    count++;
                } else
                    LOG.error("Parse error in line: " + line);
            }
            
            LOG.info("Number of elements read for vector = " + count);
        }
    }
    
    @Override
    protected void map(LongWritable key, Text value,
            Mapper<LongWritable, Text, IntWritable, DoubleWritable>.Context context)
            throws IOException, InterruptedException {
        
        String[] split_line = value.toString().split(",");
        
        if (split_line.length == 3) {
            
            int i = Integer.parseInt(split_line[0]);
            int j = Integer.parseInt(split_line[1]);
            double aij = Double.parseDouble(split_line[2]);
            
            // y_i = sum aij*xj
            row.set(i);
            aij_x_vj.set(aij * x_i[j]);
            
            context.write(row, aij_x_vj);
        } else
            LOG.error("Error parsing line " + value);
        
    }
}
