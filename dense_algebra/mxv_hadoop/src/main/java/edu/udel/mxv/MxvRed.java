package edu.udel.mxv;

import java.io.IOException;

import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapreduce.Reducer;

/**
 * Sums up all the aij*xj values associated with each yi.
 * The output is: 
 *      - key  = the row number in vector y
 *      - value = value for that element of the vector
 */
public class MxvRed extends Reducer<IntWritable, DoubleWritable, IntWritable, DoubleWritable>{
    
    private final DoubleWritable yi = new DoubleWritable();
    
    @Override
    protected void reduce(
            IntWritable row,
            Iterable<DoubleWritable> values,
            Reducer<IntWritable, DoubleWritable, IntWritable, DoubleWritable>.Context context)
            throws IOException, InterruptedException {
        
        double result = 0;
        for (DoubleWritable val : values) {
            result += val.get();
        }
        yi.set(result);
        context.write(row, yi);
    }
}
