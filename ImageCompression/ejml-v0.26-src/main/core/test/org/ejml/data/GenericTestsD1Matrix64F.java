/*
 * Copyright (c) 2009-2013, Peter Abeles. All Rights Reserved.
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

package org.ejml.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;


/**
 * @author Peter Abeles
 */
public abstract class GenericTestsD1Matrix64F extends GenericTestsMatrix64F {

    protected abstract D1Matrix64F createMatrix( int numRows , int numCols );

    public void allTests() {
        super.allTests();
        testReshape();
        testSetAndGet_1D();
    }

    public void testReshape() {
        D1Matrix64F mat = createMatrix(3,2);

        double []origData = mat.getData();

        mat.reshape(6,1, false);

        assertTrue(origData == mat.getData());
        assertEquals(1,mat.getNumCols());
        assertEquals(6,mat.getNumRows());
    }

    public void testSetAndGet_1D() {
        D1Matrix64F mat = createMatrix(3,4);

        int indexA = mat.getIndex(1,2);
        int indexB = mat.getIndex(2,1);

        assertTrue(indexA!=indexB);

        mat.set(indexA,2.0);

        assertEquals(0,mat.get(indexB),1e-6);
        assertEquals(2,mat.get(indexA),1e-6);
    }
}