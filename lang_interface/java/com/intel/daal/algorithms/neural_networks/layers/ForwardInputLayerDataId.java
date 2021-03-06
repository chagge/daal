/* file: ForwardInputLayerDataId.java */
/*******************************************************************************
* Copyright 2014-2016 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

package com.intel.daal.algorithms.neural_networks.layers;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__FORWARDINPUTLAYERDATAID"></a>
 * \brief Available identifiers of input objects for the forward layer
 */
public final class ForwardInputLayerDataId {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    private int _value;

    /**
     * Constructs the input object identifier using the provided value
     * @param value     Value of the input object identifier
     */
    public ForwardInputLayerDataId(int value) {
        _value = value;
    }

    /**
     * Returns the value corresponding to the identifier of input object
     * \return Value corresponding to the identifier
     */
    public int getValue() {
        return _value;
    }

    private static final int inputLayerDataId = 3;

    public static final ForwardInputLayerDataId inputLayerData = new ForwardInputLayerDataId(inputLayerDataId); /*!< Input data */
}
