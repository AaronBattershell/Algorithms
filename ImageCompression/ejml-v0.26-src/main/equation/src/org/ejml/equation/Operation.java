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

package org.ejml.equation;

import org.ejml.alg.dense.mult.VectorVectorMult;
import org.ejml.data.DenseMatrix64F;
import org.ejml.factory.LinearSolverFactory;
import org.ejml.interfaces.linsol.LinearSolver;
import org.ejml.ops.CommonOps;
import org.ejml.ops.MatrixFeatures;
import org.ejml.ops.NormOps;

import java.util.List;

/**
 * Performs math operations.
 *
 * @author Peter Abeles
 */
public abstract class Operation {

    String name;

    protected Operation(String name) {
        this.name = name;
    }

    public abstract void process();

    public String name() {
        return name;
    }

    /**
     * If the variable is a local temporary variable it will be resized so that the operation can complete.  If not
     * temporary then it will not be reshaped
     * @param mat Variable containing the matrix
     * @param numRows Desired number of rows
     * @param numCols Desired number of columns
     */
    protected void resize( VariableMatrix mat , int numRows , int numCols ) {
        if( mat.isTemp() ) {
            mat.matrix.reshape(numRows,numCols);
        }
    }

    public static Info multiply(final Variable A, final Variable B, ManagerTempVariables manager) {

        Info ret = new Info();

        if( A instanceof VariableMatrix && B instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("multiply-mm") {
                @Override
                public void process() {
                    VariableMatrix mA = (VariableMatrix)A;
                    VariableMatrix mB = (VariableMatrix)B;

                    resize(output,mA.matrix.numRows,mB.matrix.numCols);
                    CommonOps.mult(mA.matrix,mB.matrix,output.matrix);
                }
            };
        } else if( A instanceof VariableInteger && B instanceof VariableInteger ) {
            final VariableInteger output = manager.createInteger();
            ret.output = output;
            ret.op = new Operation("multiply-ii") {
                @Override
                public void process() {
                    VariableInteger mA = (VariableInteger)A;
                    VariableInteger mB = (VariableInteger)B;

                    output.value = mA.value*mB.value;
                }
            };
        } else if( A instanceof VariableScalar && B instanceof VariableScalar ) {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("multiply-ss") {
                @Override
                public void process() {
                    VariableScalar mA = (VariableScalar)A;
                    VariableScalar mB = (VariableScalar)B;

                    output.value = mA.getDouble()*mB.getDouble();
                }
            };
        } else {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            final VariableMatrix m;
            final VariableScalar s;

            if( A instanceof VariableMatrix ) {
                m = (VariableMatrix)A;
                s = (VariableScalar)B;
            } else {
                m = (VariableMatrix)B;
                s = (VariableScalar)A;
            }

            ret.op = new Operation("multiply-ms") {
                @Override
                public void process() {
                    output.matrix.reshape(m.matrix.numRows,m.matrix.numCols);
                    CommonOps.scale(s.getDouble(),m.matrix,output.matrix);
                }
            };
        }

        return ret;
    }

    public static Info divide(final Variable A, final Variable B, ManagerTempVariables manager) {

        Info ret = new Info();

        if( A instanceof VariableMatrix && B instanceof VariableMatrix ) {
            return solve(B,A,manager);
        } else if( A instanceof VariableMatrix && B instanceof VariableScalar ) {
            final VariableMatrix output = manager.createMatrix();
            final VariableMatrix m = (VariableMatrix)A;
            final VariableScalar s = (VariableScalar)B;
            ret.output = output;
            ret.op = new Operation("divide-ma") {
                @Override
                public void process() {
                    output.matrix.reshape(m.matrix.numRows,m.matrix.numCols);
                    CommonOps.divide(m.matrix,s.getDouble(),output.matrix);
                }
            };
        } else if( A instanceof VariableScalar && B instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            final VariableMatrix m = (VariableMatrix)B;
            final VariableScalar s = (VariableScalar)A;
            ret.output = output;
            ret.op = new Operation("divide-ma") {
                @Override
                public void process() {
                    output.matrix.reshape(m.matrix.numRows,m.matrix.numCols);
                    CommonOps.divide(s.getDouble(),m.matrix,output.matrix);
                }
            };
        } else if( A instanceof VariableInteger && B instanceof VariableInteger ) {
            final VariableInteger output = manager.createInteger();
            ret.output = output;
            ret.op = new Operation("divide-ii") {
                @Override
                public void process() {
                    VariableInteger mA = (VariableInteger)A;
                    VariableInteger mB = (VariableInteger)B;

                    output.value = mA.value/mB.value;
                }
            };
        } else {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("divide-ss") {
                @Override
                public void process() {
                    VariableScalar mA = (VariableScalar)A;
                    VariableScalar mB = (VariableScalar)B;

                    output.value = mA.getDouble()/mB.getDouble();
                }
            };
        }

        return ret;
    }

    /**
     * Returns the negative of the input variable
     */
    public static Info neg(final Variable A, ManagerTempVariables manager) {
        Info ret = new Info();

        if( A instanceof VariableInteger  ) {
            final VariableInteger output = manager.createInteger();
            ret.output = output;
            ret.op = new Operation("neg-i") {
                @Override
                public void process() {
                    output.value = -((VariableInteger)A).value;
                }
            };
        } else if( A instanceof VariableScalar  ) {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("neg-s") {
                @Override
                public void process() {
                    output.value = -((VariableScalar)A).getDouble();
                }
            };
        } else if( A instanceof VariableMatrix  ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("neg-m") {
                @Override
                public void process() {
                    DenseMatrix64F a = ((VariableMatrix)A).matrix;
                    output.matrix.reshape(a.numRows, a.numCols);
                    CommonOps.changeSign(a, output.matrix);
                }
            };
        } else {
            throw new RuntimeException("Unsupported variable "+A);
        }

        return ret;
    }

    public static Info pow(final Variable A, final Variable B, ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableDouble output = manager.createDouble();
        ret.output = output;

        if( A instanceof VariableScalar && B instanceof VariableScalar ) {

            ret.op = new Operation("pow-ss") {
                @Override
                public void process() {
                    double a = ((VariableScalar)A).getDouble();
                    double b = ((VariableScalar)B).getDouble();

                    output.value = Math.pow(a,b);
                }
            };
        } else {
            throw new RuntimeException("Only scalar to scalar power supported");
        }

        return ret;
    }

    public static Info atan2(final Variable A, final Variable B, ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableDouble output = manager.createDouble();
        ret.output = output;

        if( A instanceof VariableScalar && B instanceof VariableScalar ) {

            ret.op = new Operation("atan2-ss") {
                @Override
                public void process() {
                    double a = ((VariableScalar)A).getDouble();
                    double b = ((VariableScalar)B).getDouble();

                    output.value = Math.atan2(a, b);
                }
            };
        } else {
            throw new RuntimeException("Only scalar to scalar atan2 supported");
        }

        return ret;
    }

    public static Info sqrt(final Variable A, ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableDouble output = manager.createDouble();
        ret.output = output;

        if( A instanceof VariableScalar  ) {

            ret.op = new Operation("sqrt-s") {
                @Override
                public void process() {
                    double a = ((VariableScalar)A).getDouble();

                    output.value = Math.sqrt(a);
                }
            };
        } else {
            throw new RuntimeException("Only scalars are supported");
        }

        return ret;
    }

    public static Info sin(final Variable A, ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableDouble output = manager.createDouble();
        ret.output = output;

        if( A instanceof VariableScalar  ) {

            ret.op = new Operation("sin-s") {
                @Override
                public void process() {
                    output.value = Math.sin(((VariableScalar) A).getDouble());
                }
            };
        } else {
            throw new RuntimeException("Only scalars are supported");
        }

        return ret;
    }

    public static Info cos(final Variable A, ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableDouble output = manager.createDouble();
        ret.output = output;

        if( A instanceof VariableScalar  ) {

            ret.op = new Operation("cos-s") {
                @Override
                public void process() {
                    output.value = Math.cos(((VariableScalar) A).getDouble());
                }
            };
        } else {
            throw new RuntimeException("Only scalars are supported");
        }

        return ret;
    }

    public static Info atan(final Variable A, ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableDouble output = manager.createDouble();
        ret.output = output;

        if( A instanceof VariableScalar  ) {

            ret.op = new Operation("atan-s") {
                @Override
                public void process() {
                    output.value = Math.atan(((VariableScalar) A).getDouble());
                }
            };
        } else {
            throw new RuntimeException("Only scalars are supported");
        }

        return ret;
    }

    public static Info exp(final Variable A, ManagerTempVariables manager) {
        final Info ret = new Info();


        if( A instanceof VariableScalar  ) {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("exp-s") {
                @Override
                public void process() {
                    output.value = Math.exp(((VariableScalar) A).getDouble());
                }
            };
        } else if( A instanceof VariableMatrix  ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("exp-m") {
                @Override
                public void process() {
                    DenseMatrix64F a = ((VariableMatrix)A).matrix;
                    DenseMatrix64F out = ((VariableMatrix)ret.output).matrix;
                    out.reshape(a.numRows,a.numCols);
                    CommonOps.elementExp(a, out);
                }
            };
        } else {
            throw new RuntimeException("Only scalars are supported");
        }

        return ret;
    }

    public static Info log(final Variable A, ManagerTempVariables manager) {
        final Info ret = new Info();

        if( A instanceof VariableScalar  ) {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("log-s") {
                @Override
                public void process() {
                    output.value = Math.log(((VariableScalar) A).getDouble());
                }
            };
        } else if( A instanceof VariableMatrix  ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("log-m") {
                @Override
                public void process() {
                    DenseMatrix64F a = ((VariableMatrix)A).matrix;
                    DenseMatrix64F out = ((VariableMatrix)ret.output).matrix;
                    out.reshape(a.numRows,a.numCols);
                    CommonOps.elementLog(a,out);
                }
            };
        } else {
            throw new RuntimeException("Only scalars are supported");
        }

        return ret;
    }

    public static Info add(final Variable A, final Variable B, ManagerTempVariables manager) {
        Info ret = new Info();

        if( A instanceof VariableMatrix && B instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("add-mm") {
                @Override
                public void process() {
                    VariableMatrix mA = (VariableMatrix)A;
                    VariableMatrix mB = (VariableMatrix)B;

                    resize(output, mA.matrix.numRows, mA.matrix.numCols);
                    CommonOps.add(mA.matrix, mB.matrix, output.matrix);
                }
            };
        } else if( A instanceof VariableInteger && B instanceof VariableInteger ) {
            final VariableInteger output = manager.createInteger(0);
            ret.output = output;
            ret.op = new Operation("add-ii") {
                @Override
                public void process() {
                    VariableInteger mA = (VariableInteger)A;
                    VariableInteger mB = (VariableInteger)B;

                    output.value = mA.value + mB.value;
                }
            };
        } else if( A instanceof VariableScalar && B instanceof VariableScalar ) {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("add-ss") {
                @Override
                public void process() {
                    VariableScalar mA = (VariableScalar)A;
                    VariableScalar mB = (VariableScalar)B;

                    output.value = mA.getDouble() + mB.getDouble();
                }
            };
        } else {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            final VariableMatrix m;
            final VariableScalar s;

            if( A instanceof VariableMatrix ) {
                m = (VariableMatrix)A;
                s = (VariableScalar)B;
            } else {
                m = (VariableMatrix)B;
                s = (VariableScalar)A;
            }

            ret.op = new Operation("add-ms") {
                @Override
                public void process() {
                    output.matrix.reshape(m.matrix.numRows,m.matrix.numCols);
                    CommonOps.add(m.matrix, s.getDouble(), output.matrix);
                }
            };
        }

        return ret;
    }

    public static Info subtract(final Variable A, final Variable B, ManagerTempVariables manager) {
        Info ret = new Info();

        if( A instanceof VariableMatrix && B instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("subtract-mm") {
                @Override
                public void process() {
                    VariableMatrix mA = (VariableMatrix)A;
                    VariableMatrix mB = (VariableMatrix)B;

                    resize(output, mA.matrix.numRows, mA.matrix.numCols);
                    CommonOps.subtract(mA.matrix, mB.matrix, output.matrix);
                }
            };
        } else if( A instanceof VariableInteger && B instanceof VariableInteger ) {
            final VariableInteger output = manager.createInteger(0);
            ret.output = output;
            ret.op = new Operation("subtract-ii") {
                @Override
                public void process() {
                    VariableInteger mA = (VariableInteger)A;
                    VariableInteger mB = (VariableInteger)B;

                    output.value = mA.value - mB.value;
                }
            };
        } else if( A instanceof VariableScalar && B instanceof VariableScalar ) {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("subtract-ss") {
                @Override
                public void process() {
                    VariableScalar mA = (VariableScalar)A;
                    VariableScalar mB = (VariableScalar)B;

                    output.value = mA.getDouble() - mB.getDouble();
                }
            };
        } else {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;

            if( A instanceof VariableMatrix ) {
                ret.op = new Operation("subtract-ms") {
                    @Override
                    public void process() {
                        DenseMatrix64F m = ((VariableMatrix)A).matrix;
                        double v = ((VariableScalar)B).getDouble();
                        output.matrix.reshape(m.numRows, m.numCols);
                        CommonOps.subtract(m, v, output.matrix);
                    }
                };
            } else {
                ret.op = new Operation("subtract-sm") {
                    @Override
                    public void process() {
                        DenseMatrix64F m = ((VariableMatrix)B).matrix;
                        double v = ((VariableScalar)A).getDouble();
                        output.matrix.reshape(m.numRows, m.numCols);
                        CommonOps.subtract(v, m, output.matrix);
                    }
                };
            }
        }

        return ret;
    }

    public static Info elementMult( final Variable A , final Variable B , ManagerTempVariables manager ) {
        Info ret = new Info();

        if( A instanceof VariableMatrix && B instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("elementMult-mm") {
                @Override
                public void process() {
                    VariableMatrix mA = (VariableMatrix)A;
                    VariableMatrix mB = (VariableMatrix)B;

                    resize(output, mA.matrix.numRows, mA.matrix.numCols);
                    CommonOps.elementMult(mA.matrix, mB.matrix, output.matrix);
                }
            };
        } else {
            throw new RuntimeException("Both inputs must be matrices for element wise multiplication");
        }

        return ret;
    }

    public static Info elementDivision( final Variable A , final Variable B , ManagerTempVariables manager ) {
        Info ret = new Info();

        if( A instanceof VariableMatrix && B instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("elementDivision-mm") {
                @Override
                public void process() {
                    VariableMatrix mA = (VariableMatrix)A;
                    VariableMatrix mB = (VariableMatrix)B;

                    resize(output, mA.matrix.numRows, mA.matrix.numCols);
                    CommonOps.elementDiv(mA.matrix, mB.matrix, output.matrix);
                }
            };
        } else {
            throw new RuntimeException("Both inputs must be matrices for element wise multiplication");
        }

        return ret;
    }

    public static Info elementPow(final Variable A, final Variable B, ManagerTempVariables manager) {
        Info ret = new Info();


        if( A instanceof VariableScalar && B instanceof VariableScalar ) {

            final VariableDouble output = manager.createDouble();
            ret.output = output;

            ret.op = new Operation("elementPow-ss") {
                @Override
                public void process() {
                    double a = ((VariableScalar) A).getDouble();
                    double b = ((VariableScalar) B).getDouble();

                    output.value = Math.pow(a, b);
                }
            };
        } else if( A instanceof VariableMatrix && B instanceof VariableMatrix ) {

            final VariableMatrix output = manager.createMatrix();
            ret.output = output;

            ret.op = new Operation("elementPow-mm") {
                @Override
                public void process() {
                    DenseMatrix64F a = ((VariableMatrix) A).matrix;
                    DenseMatrix64F b = ((VariableMatrix) B).matrix;

                    resize(output, a.numRows, a.numCols);
                    CommonOps.elementPower(a, b, output.matrix);
                }
            };
        } else if( A instanceof VariableMatrix && B instanceof VariableScalar ) {

            final VariableMatrix output = manager.createMatrix();
            ret.output = output;

            ret.op = new Operation("elementPow-ms") {
                @Override
                public void process() {
                    DenseMatrix64F a = ((VariableMatrix) A).matrix;
                    double b = ((VariableScalar) B).getDouble();

                    resize(output, a.numRows, a.numCols);
                    CommonOps.elementPower(a, b, output.matrix);
                }
            };
        } else if( A instanceof VariableScalar && B instanceof VariableMatrix ) {

            final VariableMatrix output = manager.createMatrix();
            ret.output = output;

            ret.op = new Operation("elementPow-sm") {
                @Override
                public void process() {
                    double a = ((VariableScalar) A).getDouble();
                    DenseMatrix64F b = ((VariableMatrix) B).matrix;

                    resize(output, b.numRows, b.numCols);
                    CommonOps.elementPower(a, b, output.matrix);
                }
            };
        } else {
            throw new RuntimeException("Unsupport element-wise power input types");
        }

        return ret;
    }

    public static Operation copy( final Variable src , final Variable dst ) {
        if( src instanceof VariableMatrix && dst instanceof VariableMatrix ) {
            return new Operation("copy-mm") {
                @Override
                public void process() {
                    DenseMatrix64F d = ((VariableMatrix)dst).matrix;
                    DenseMatrix64F s = ((VariableMatrix)src).matrix;
                    d.reshape(s.numRows,s.numCols);
                    d.set(((VariableMatrix) src).matrix);
                }
            };
        } else if( src instanceof VariableInteger && dst instanceof VariableInteger ) {
            return new Operation("copy-ii") {
                @Override
                public void process() {
                    ((VariableInteger)dst).value = ((VariableInteger)src).value;
                }
            };
        } else if( src instanceof VariableScalar && dst instanceof VariableDouble ) {
            return new Operation("copy-ss") {
                @Override
                public void process() {
                    ((VariableDouble)dst).value = ((VariableScalar)src).getDouble();
                }
            };
        } else {
            throw new RuntimeException("Copy type miss-match src = "+src.getClass().getSimpleName()+" dst = "+dst.getClass().getSimpleName());
        }
    }

    public static Operation copy( final Variable src , final Variable dst , final List<Variable> range ) {
        if( src instanceof VariableMatrix && dst instanceof VariableMatrix ) {
            return new Operation("copyR-mm") {
                Extents extents = new Extents();

                @Override
                public void process() {

                    DenseMatrix64F msrc = ((VariableMatrix) src).matrix;
                    DenseMatrix64F mdst = ((VariableMatrix) dst).matrix;

                    findExtents(mdst, range, 0, extents);

                    if (extents.col1 - extents.col0 != msrc.numCols)
                        throw new RuntimeException("Columns don't match");
                    if (extents.row1 - extents.row0 != msrc.numRows)
                        throw new RuntimeException("Rows don't match");

                    CommonOps.insert(msrc, mdst, extents.row0, extents.col0);
                }
            };
        } else if( src instanceof VariableScalar && dst instanceof VariableMatrix ) {
            return new Operation("copyR-sm") {
                Extents extents = new Extents();

                @Override
                public void process() {

                    double msrc = ((VariableScalar)src).getDouble();
                    DenseMatrix64F mdst = ((VariableMatrix)dst).matrix;

                    findExtents(mdst,range,0,extents);

                    if( !mdst.isInBounds(extents.col0,extents.row0))
                        throw new RuntimeException("Submatrix out of bounds. Lower extent");
                    if( !mdst.isInBounds(extents.col1-1,extents.row1-1))
                        throw new RuntimeException("Submatrix out of bounds. Upper extent");

                    for (int i = extents.row0; i < extents.row1; i++) {
                        int index = i*mdst.numCols + extents.col0;
                        for (int j = extents.col0; j < extents.col1; j++) {
                            mdst.data[index++] = msrc;
                        }
                    }
                }
            };
        } else {
            throw new RuntimeException("Both variables must be of type VariableMatrix");
        }
    }

    public static Info transpose( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();

        if( A instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("transpose-m") {
                @Override
                public void process() {
                    VariableMatrix mA = (VariableMatrix)A;
                    output.matrix.reshape(mA.matrix.numCols, mA.matrix.numRows);
                    CommonOps.transpose(mA.matrix, output.matrix);
                }
            };
        } else {
            throw new RuntimeException("Transpose only makes sense for a matrix");
        }
        return ret;
    }

    /**
     * Matrix inverse
     */
    public static Info inv( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();

        if( A instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("inv-m") {
                @Override
                public void process() {
                    VariableMatrix mA = (VariableMatrix)A;
                    output.matrix.reshape(mA.matrix.numRows,mA.matrix.numCols);
                    if( !CommonOps.invert(mA.matrix,output.matrix) )
                        throw new RuntimeException("Inverse failed!");
                }
            };
        } else {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("inv-s") {
                @Override
                public void process() {
                    VariableScalar mA = (VariableScalar)A;
                    output.value = 1.0/mA.getDouble();
                }
            };
        }

        return ret;
    }

    /**
     * Matrix pseudo-inverse
     */
    public static Info pinv( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();

        if( A instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("pinv-m") {
                @Override
                public void process() {
                    VariableMatrix mA = (VariableMatrix)A;
                    output.matrix.reshape(mA.matrix.numCols, mA.matrix.numRows);
                    CommonOps.pinv(mA.matrix, output.matrix);
                }
            };
        } else {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("pinv-s") {
                @Override
                public void process() {
                    VariableScalar mA = (VariableScalar)A;
                    output.value = 1.0/mA.getDouble();
                }
            };
        }

        return ret;
    }

    public static Info rref( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();

        if( A instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("rref-m") {
                @Override
                public void process() {
                    DenseMatrix64F a = ((VariableMatrix)A).matrix;
                    output.matrix.reshape(a.numRows,a.numCols);
                    CommonOps.rref(a, -1, output.matrix);
                }
            };
        } else {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("rref-s") {
                @Override
                public void process() {
                    double a = ((VariableScalar)A).getDouble();
                    output.value = a == 0 ? 0 : 1;
                }
            };
        }

        return ret;
    }

    /**
     * Matrix determinant
     */
    public static Info det( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();

        final VariableDouble output = manager.createDouble();
        ret.output = output;

        if( A instanceof VariableMatrix ) {
            ret.op = new Operation("det-m") {
                @Override
                public void process() {
                    VariableMatrix mA = (VariableMatrix)A;
                    output.value = CommonOps.det(mA.matrix);
                }
            };
        } else {
            ret.op = new Operation("det-s") {
                @Override
                public void process() {
                    VariableScalar mA = (VariableScalar)A;
                    output.value = mA.getDouble();
                }
            };
        }

        return ret;
    }

    public static Info trace( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableDouble output = manager.createDouble();
        ret.output = output;

        if( A instanceof VariableMatrix ) {
            ret.op = new Operation("trace-m") {
                @Override
                public void process() {
                    VariableMatrix mA = (VariableMatrix)A;
                    output.value=CommonOps.trace(mA.matrix);
                }
            };
        } else {
            ret.op = new Operation("trace-s") {
                @Override
                public void process() {
                    VariableScalar mA = (VariableScalar)A;
                    output.value = mA.getDouble();
                }
            };
        }

        return ret;
    }

    public static Info normF( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableDouble output = manager.createDouble();
        ret.output = output;

        if( A instanceof VariableMatrix ) {
            ret.op = new Operation("normF-m") {
                @Override
                public void process() {
                    output.value= NormOps.normF(((VariableMatrix)A).matrix);
                }
            };
        } else {
            ret.op = new Operation("normF-s") {
                @Override
                public void process() {
                    output.value = Math.abs(((VariableScalar) A).getDouble());
                }
            };
        }

        return ret;
    }


    public static Info max( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();

        if( A instanceof VariableMatrix ) {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("max-m") {
                @Override
                public void process() {
                    output.value = CommonOps.elementMax(((VariableMatrix) A).matrix);
                }
            };
        } else if( A instanceof VariableInteger ) {
            final VariableInteger output = manager.createInteger();
            ret.output = output;
            ret.op = new Operation("max-i") {
                @Override
                public void process() {
                    output.value = ((VariableInteger)A).value;
                }
            };
        } else if( A instanceof VariableScalar ) {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("max-s") {
                @Override
                public void process() {
                    output.value = ((VariableDouble)A).getDouble();
                }
            };
        }

        return ret;
    }

    public static Info min( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();

        if( A instanceof VariableMatrix ) {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("min-m") {
                @Override
                public void process() {
                    output.value = CommonOps.elementMin(((VariableMatrix) A).matrix);
                }
            };
        } else if( A instanceof VariableInteger ) {
            final VariableInteger output = manager.createInteger();
            ret.output = output;
            ret.op = new Operation("min-i") {
                @Override
                public void process() {
                    output.value = ((VariableInteger)A).value;
                }
            };
        } else if( A instanceof VariableScalar ) {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("min-s") {
                @Override
                public void process() {
                    output.value = ((VariableDouble)A).getDouble();
                }
            };
        }

        return ret;
    }

    public static Info abs( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();

        if( A instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("abs-m") {
                @Override
                public void process() {
                    DenseMatrix64F a = ((VariableMatrix)A).matrix;
                    output.matrix.reshape(a.numRows,a.numCols);
                    int N = a.getNumElements();
                    for (int i = 0; i < N; i++) {
                        output.matrix.data[i] = Math.abs(a.data[i]);
                    }
                }
            };
        } else if( A instanceof VariableInteger ) {
            final VariableInteger output = manager.createInteger();
            ret.output = output;
            ret.op = new Operation("abs-i") {
                @Override
                public void process() {
                    output.value = Math.abs(((VariableInteger)A).value);
                }
            };
        } else if( A instanceof VariableScalar ) {
            final VariableDouble output = manager.createDouble();
            ret.output = output;
            ret.op = new Operation("abs-s") {
                @Override
                public void process() {
                    output.value = Math.abs((((VariableDouble)A).getDouble()));
                }
            };
        }

        return ret;
    }

    /**
     * Returns an identity matrix
     */
    public static Info eye( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableMatrix output = manager.createMatrix();
        ret.output = output;

        if( A instanceof VariableMatrix ) {
            ret.op = new Operation("eye-m") {
                @Override
                public void process() {
                    DenseMatrix64F mA = ((VariableMatrix)A).matrix;
                    output.matrix.reshape(mA.numRows,mA.numCols);
                    CommonOps.setIdentity(output.matrix);
                }
            };
        } else if( A instanceof VariableInteger ) {
            ret.op = new Operation("eye-i") {
                @Override
                public void process() {
                    int N = ((VariableInteger)A).value;
                    output.matrix.reshape(N,N);
                    CommonOps.setIdentity(output.matrix);
                }
            };
        } else {
            throw new RuntimeException("Unsupported variable type "+A);
        }

        return ret;
    }

    public static Info diag( final Variable A , ManagerTempVariables manager) {
        Info ret = new Info();

        if( A instanceof VariableMatrix ) {
            final VariableMatrix output = manager.createMatrix();
            ret.output = output;
            ret.op = new Operation("diag-m") {
                @Override
                public void process() {
                    DenseMatrix64F mA = ((VariableMatrix)A).matrix;

                    if(MatrixFeatures.isVector(mA)) {
                        int N = mA.getNumElements();
                        output.matrix.reshape(N,N);
                        CommonOps.diag(output.matrix,N,mA.data);
                    } else {
                        int N = Math.min(mA.numCols,mA.numRows);
                        output.matrix.reshape(N,1);
                        for (int i = 0; i < N; i++) {
                            output.matrix.data[i] = mA.unsafe_get(i,i);
                        }
                    }
                }
            };
        } else {
            throw new RuntimeException("diag requires a matrix as input");
        }
        return ret;
    }

    /**
     * Returns a matrix full of zeros
     */
    public static Info zeros( final Variable A , final Variable B , ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableMatrix output = manager.createMatrix();
        ret.output = output;

        if( A instanceof VariableInteger && B instanceof VariableInteger ) {
            ret.op = new Operation("zeros-ii") {
                @Override
                public void process() {
                    int numRows = ((VariableInteger)A).value;
                    int numCols = ((VariableInteger)B).value;
                    output.matrix.reshape(numRows,numCols);
                    CommonOps.fill(output.matrix,0);
                    //not sure if this is necessary.  Can its value every be modified?
                }
            };
        } else {
            throw new RuntimeException("Expected two integers got "+A+" "+B);
        }

        return ret;
    }

    /**
     * Returns a matrix full of ones
     */
    public static Info ones( final Variable A , final Variable B , ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableMatrix output = manager.createMatrix();
        ret.output = output;

        if( A instanceof VariableInteger && B instanceof VariableInteger ) {
            ret.op = new Operation("ones-ii") {
                @Override
                public void process() {
                    int numRows = ((VariableInteger)A).value;
                    int numCols = ((VariableInteger)B).value;
                    output.matrix.reshape(numRows,numCols);
                    CommonOps.fill(output.matrix,1);
                }
            };
        } else {
            throw new RuntimeException("Expected two integers got "+A+" "+B);
        }

        return ret;
    }

    /**
     * Kronecker product
     */
    public static Info kron( final Variable A , final Variable B, ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableMatrix output = manager.createMatrix();
        ret.output = output;

        if( A instanceof VariableMatrix && B instanceof VariableMatrix ) {
            ret.op = new Operation("kron-mm") {
                @Override
                public void process() {
                    DenseMatrix64F mA = ((VariableMatrix)A).matrix;
                    DenseMatrix64F mB = ((VariableMatrix)B).matrix;
                    output.matrix.reshape(mA.numRows * mB.numRows, mA.numCols * mB.numCols);
                    CommonOps.kron(mA, mB, output.matrix);
                }
            };
        } else {
            throw new RuntimeException("Both inputs must be matrices ");
        }

        return ret;
    }

    /**
     * If input is two vectors then it returns the dot product as a double.
     */
    public static Info dot( final Variable A , final Variable B , ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableDouble output = manager.createDouble();
        ret.output = output;

        if( A instanceof VariableMatrix && B instanceof VariableMatrix ) {
            ret.op = new Operation("dot-mm") {
                @Override
                public void process() {
                    DenseMatrix64F a = ((VariableMatrix)A).matrix;
                    DenseMatrix64F b = ((VariableMatrix)B).matrix;

                    if( !MatrixFeatures.isVector(a) || !MatrixFeatures.isVector(b))
                        throw new RuntimeException("Both inputs to dot() must be vectors");

                    output.value = VectorVectorMult.innerProd(a,b);
                }
            };
        } else {
            throw new RuntimeException("Expected two matrices got "+A+" "+B);
        }

        return ret;
    }

    /**
     * If input is two vectors then it returns the dot product as a double.
     */
    public static Info solve( final Variable A , final Variable B , ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableMatrix output = manager.createMatrix();
        ret.output = output;

        if( A instanceof VariableMatrix && B instanceof VariableMatrix ) {
            ret.op = new Operation("solve-mm") {
                LinearSolver<DenseMatrix64F> solver;
                @Override
                public void process() {

                    DenseMatrix64F a = ((VariableMatrix)A).matrix;
                    DenseMatrix64F b = ((VariableMatrix)B).matrix;

                    if( solver == null ) {
                        solver = LinearSolverFactory.leastSquares(a.numRows,a.numCols);
                    }

                    if( !solver.setA(a))
                        throw new RuntimeException("Solver failed!");

                    output.matrix.reshape(a.numCols,b.numCols);
                    solver.solve(b, output.matrix);
                }
            };
        } else {
            throw new RuntimeException("Expected two matrices got "+A+" "+B);
        }

        return ret;
    }

    public static Info extract( final List<Variable> inputs, ManagerTempVariables manager) {
        Info ret = new Info();
        final VariableMatrix output = manager.createMatrix();
        ret.output = output;

        if(  !(inputs.get(0) instanceof VariableMatrix))
            throw new RuntimeException("First parameter must be a matrix.");

        for (int i = 1; i < inputs.size(); i++) {
            if( !(inputs.get(i) instanceof VariableInteger) && !(inputs.get(i) instanceof VariableSpecial) )
                throw new RuntimeException("Last parameters must be integers or special for sub");
        }

        ret.op = new Operation("extract") {

            Extents extents = new Extents();

            @Override
            public void process() {

                DenseMatrix64F A = ((VariableMatrix)inputs.get(0)).matrix;

                findExtents(A,inputs,1,extents);

                output.matrix.reshape(extents.row1-extents.row0,extents.col1-extents.col0);
                CommonOps.extract(A,extents.row0,extents.row1,extents.col0,extents.col1,output.matrix,0,0);
            }
        };

        return ret;
    }

    /**
     * Parses the inputs to figure out the range of a sub-matrix.  Special variables are handled to set
     * relative values
     */
    protected static void findExtents( DenseMatrix64F A, List<Variable> inputs , int where ,Extents e ) {
        if( inputs.get(where).getType() == VariableType.SPECIAL ) {
            e.row0 = 0; e.row1 = A.numRows; where++;
        } else {
            e.row0 = ((VariableInteger)inputs.get(where++)).value;
            if( inputs.get(where).getType() == VariableType.SPECIAL ) {
                e.row1 = A.numRows;
            } else {
                e.row1 = ((VariableInteger)inputs.get(where)).value+1;
            }
            where++;
        }

        if( inputs.get(where).getType() == VariableType.SPECIAL ) {
            e.col0 = 0; e.col1 = A.numCols; where++;
        } else {
            e.col0 = ((VariableInteger)inputs.get(where++)).value;
            if( inputs.get(where).getType() == VariableType.SPECIAL ) {
                e.col1 = A.numCols;
            } else {
                e.col1 = ((VariableInteger)inputs.get(where)).value+1;
            }
            where++;
        }

        if( where != inputs.size())
            throw new RuntimeException("Unexpected number of inputs");
    }

    public static Info matrixConstructor( final MatrixConstructor m ) {
        Info ret = new Info();
        ret.output = m.getOutput();

        ret.op = new Operation("matrixConstructor") {

            @Override
            public void process() {
                m.construct();
            }
        };

        return ret;
    }

    public static class Extents
    {
        int row0,row1;
        int col0,col1;
    }

    public static class Info
    {
        public Operation op;
        public Variable output;
    }
}
