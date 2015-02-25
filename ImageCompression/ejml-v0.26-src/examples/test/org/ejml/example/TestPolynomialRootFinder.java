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

package org.ejml.example;

import org.ejml.data.Complex64F;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

/**
 * @author Peter Abeles
 */
public class TestPolynomialRootFinder {

    @Test
    public void findRoots() {
        Complex64F[] roots = PolynomialRootFinder.findRoots(4, 3, 2, 1);

        int numReal = 0;
        for( Complex64F c : roots ) {
            if( c.isReal() ) {
                checkRoot(c.real,4,3,2,1);
                numReal++;
            }
        }

        assertTrue(numReal>0);
    }

    private void checkRoot( double root , double ...coefs ) {
        double total = 0;

        double a = 1;
        for( double c : coefs ) {
            total += a*c;
            a *= root;
        }

        assertEquals(0,total,1e-8);
    }
}