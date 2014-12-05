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

import java.io.IOException;

import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapreduce.Reducer;

/**
 * Sums up all the aij*xj values associated with each yi.
 * The output is: 
 *      - key  = the row number in vector y
 *      - value = value for that element of the vector
 *      
 * @author Sergio Pino sergiop@udel.edu
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
