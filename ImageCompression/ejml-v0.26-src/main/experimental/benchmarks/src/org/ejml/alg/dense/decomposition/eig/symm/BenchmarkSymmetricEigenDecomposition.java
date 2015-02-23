/*
 * Copyright (c) 2009-2014, Peter Abeles. All Rights Reserved.
 *
 * This file is part of Efficient Java Matrix Library (EJML).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.ejml.alg.dense.decomposition.eig.symm;

import org.ejml.alg.dense.decomposition.eig.SymmetricQRAlgorithmDecomposition_D64;
import org.ejml.alg.dense.decomposition.hessenberg.TridiagonalDecompositionHouseholder_D64;
import org.ejml.alg.dense.decomposition.hessenberg.TridiagonalDecomposition_B64_to_D64;
import org.ejml.data.DenseMatrix64F;
import org.ejml.factory.DecompositionFactory;
import org.ejml.interfaces.decomposition.EigenDecomposition;
import org.ejml.interfaces.decomposition.TridiagonalSimilarDecomposition;
import org.ejml.ops.RandomMatrices;

import java.util.Random;


/**
 * @author Peter Abeles
 */
public class BenchmarkSymmetricEigenDecomposition {
    public static long symmTogether( DenseMatrix64F orig , int numTrials ) {

        long prev = System.currentTimeMillis();

        TridiagonalSimilarDecomposition<DenseMatrix64F> decomp =  DecompositionFactory.tridiagonal(orig.numRows);
        SymmetricQRAlgorithmDecomposition_D64 alg = new SymmetricQRAlgorithmDecomposition_D64(decomp,true);

        alg.setComputeVectorsWithValues(true);

        for( long i = 0; i < numTrials; i++ ) {
            if( !DecompositionFactory.decomposeSafe(alg,orig) ) {
                throw new RuntimeException("Bad matrix");
            }
        }

        return System.currentTimeMillis() - prev;
    }

    public static long symmSeparate( DenseMatrix64F orig , int numTrials ) {

        long prev = System.currentTimeMillis();

        TridiagonalSimilarDecomposition<DenseMatrix64F> decomp =  DecompositionFactory.tridiagonal(orig.numRows);
        SymmetricQRAlgorithmDecomposition_D64 alg = new SymmetricQRAlgorithmDecomposition_D64(decomp,true);

        alg.setComputeVectorsWithValues(false);

        for( long i = 0; i < numTrials; i++ ) {
            if( !DecompositionFactory.decomposeSafe(alg,orig) ) {
                throw new RuntimeException("Bad matrix");
            }
        }

        return System.currentTimeMillis() - prev;
    }

    public static long standardTridiag( DenseMatrix64F orig , int numTrials ) {
        TridiagonalSimilarDecomposition<DenseMatrix64F> decomp = new TridiagonalDecompositionHouseholder_D64();
        SymmetricQRAlgorithmDecomposition_D64 alg = new SymmetricQRAlgorithmDecomposition_D64(decomp,true);

        long prev = System.currentTimeMillis();

        for( long i = 0; i < numTrials; i++ ) {
            if( !DecompositionFactory.decomposeSafe(alg,orig) ) {
                throw new RuntimeException("Bad matrix");
            }
        }

        return System.currentTimeMillis() - prev;
    }

    public static long blockTridiag( DenseMatrix64F orig , int numTrials ) {

        TridiagonalSimilarDecomposition<DenseMatrix64F> decomp = new TridiagonalDecomposition_B64_to_D64();
        SymmetricQRAlgorithmDecomposition_D64 alg = new SymmetricQRAlgorithmDecomposition_D64(decomp,true);

        long prev = System.currentTimeMillis();

        for( long i = 0; i < numTrials; i++ ) {
            if( !DecompositionFactory.decomposeSafe(alg,orig) ) {
                throw new RuntimeException("Bad matrix");
            }
        }

        return System.currentTimeMillis() - prev;
    }

    public static long defaultSymm( DenseMatrix64F orig , int numTrials ) {

        EigenDecomposition<DenseMatrix64F> alg = DecompositionFactory.eig(orig.numCols, true, true);

        long prev = System.currentTimeMillis();

        for( long i = 0; i < numTrials; i++ ) {
            if( !DecompositionFactory.decomposeSafe(alg,orig) ) {
                throw new RuntimeException("Bad matrix");
            }
        }

        return System.currentTimeMillis() - prev;
    }


    private static void runAlgorithms( DenseMatrix64F mat , int numTrials )
    {
//        System.out.println("Together            = "+ symmTogether(mat,numTrials));
//        System.out.println("Separate            = "+ symmSeparate(mat,numTrials));
        System.out.println("Standard            = "+ standardTridiag(mat,numTrials));
        System.out.println("Block               = "+ blockTridiag(mat,numTrials));
        System.out.println("Default             = "+ defaultSymm(mat,numTrials));
    }

    public static void main( String args [] ) {
        Random rand = new Random(232423);

        int size[] = new int[]{2,4,10,100,200,500,1000,2000,5000};
        int trials[] = new int[]{2000000,400000,80000,300,40,4,1,1,1};

        for( int i = 0; i < size.length; i++ ) {
            int w = size[i];

            System.out.printf("Decomposing size %3d for %12d trials\n",w,trials[i]);

            DenseMatrix64F symMat = RandomMatrices.createSymmetric(w,-1,1,rand);

            runAlgorithms(symMat,trials[i]);
        }
    }
}