package me.algos2.svdproj;

import java.nio.ByteBuffer;
import java.nio.FloatBuffer;

/**
 * Created by chuka on 4/5/15.
 */
public class encodeDecode {

    //We would accept the float array as a one dimensional array for simplicity purpose
    //and I can also include implementation for writing to file after decoding in the morning

    public byte[] encode(float myfloatArray[]){

            byte mybyteArray[] = new byte[myfloatArray.length*4];
            ByteBuffer byteBuffer = ByteBuffer.wrap(mybyteArray);
            FloatBuffer floatBuf = byteBuffer.asFloatBuffer();
            floatBuf.put (myfloatArray);

            return mybyteArray;

    }

    public float[] decode(byte mybyteArray[]) {

        float myfloatArray[] = new float[mybyteArray.length/4];
        ByteBuffer byteBuf = ByteBuffer.wrap(mybyteArray);
        FloatBuffer floatBuf = byteBuf.asFloatBuffer();
        floatBuf.get (myfloatArray);

        return myfloatArray;
    }
}
