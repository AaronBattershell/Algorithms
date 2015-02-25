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

package org.ejml.alg.dense.decomposition.chol;

import org.ejml.data.DenseMatrix64F;
import org.ejml.interfaces.decomposition.CholeskyDecomposition;
import org.junit.Test;

import static org.ejml.alg.dense.decomposition.CheckDecompositionInterface.checkModifiedInput;


/**
 * @author Peter Abeles
 */
public class TestCholeskyDecompositionInner_D64 extends GenericCholeskyTests {

    @Override
    public CholeskyDecomposition<DenseMatrix64F> create(boolean lower) {
        return new CholeskyDecompositionInner_D64(lower);
    }

    @Test
    public void checkModifyInput() {
        checkModifiedInput(new CholeskyDecompositionInner_D64(true));
        checkModifiedInput(new CholeskyDecompositionInner_D64(false));
    }
}
