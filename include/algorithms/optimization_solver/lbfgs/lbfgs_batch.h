/* file: lbfgs_batch.h */
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

/*
//++
//  Implementation of the interface for the limited-memory Broyden-Fletcher-Goldfarb-Shanno
//  (BFGS) algorithm in the batch processing mode
//--
*/

#ifndef __LBFGS_BATCH_H__
#define __LBFGS_BATCH_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/optimization_solver/iterative_solver/iterative_solver_batch.h"
#include "lbfgs_types.h"

namespace daal
{
namespace algorithms
{
namespace optimization_solver
{
namespace lbfgs
{
namespace interface1
{
/**
 * @defgroup lbfgs_batch Batch
 * @ingroup lbfgs
 * @{
 */
/**
 * <a name="DAAL-CLASS-ALGORITHMS__OPTIMIZATION_SOLVER__LBFGS__BATCHCONTAINER"></a>
 * \brief Provides methods to run implementations of the LBFGS algorithm.
 *        This class is associated with daal::algorithms::optimization_solver::lbfgs::Batch class.
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the LBFGS algorithm, double or float
 * \tparam method           Stochastic gradient descent computation method, daal::algorithms::optimization_solver::lbfgs::Method
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public daal::algorithms::AnalysisContainerIface<batch>
{
public:
    /**
     * Constructs a container for the limited-memory BFGS algorithm with a specified environment
     * in the batch processing mode
     * \param[in] daalEnv   Environment object
     */
    BatchContainer(daal::services::Environment::env *daalEnv);
    /** Default destructor */
    ~BatchContainer();
    /**
     * Computes the result of the limited-memory BFGS algorithm in the batch processing mode
     */
    virtual void compute() DAAL_C11_OVERRIDE;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__OPTIMIZATION_SOLVER__LBFGS__BATCH"></a>
 * \brief Computes LBFGS in the batch processing mode.
 * \n<a href="DAAL-REF-LBFGS-ALGORITHM">Limited memory BFGS algorithm description and usage models</a>
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the LBFGS algorithm,
 *                          double or float
 * \tparam method           LBFGS computation method
 *
 * \par Enumerations
 *      - \ref Method   Computation methods for LBFGS
 *      - \ref iterative_solver::InputId  Identifiers of input objects for LBFGS
 *      - \ref iterative_solver::ResultId optimization_solver::Result identifiers for the LBFGS
 *
 * \par References
 *      - Input class
 *      - Result class
 */
template<typename algorithmFPType = double, Method method = defaultDense>
class DAAL_EXPORT Batch : public iterative_solver::Batch
{
public:
    Input input;         /*!< %Input data structure */
    Parameter parameter;   /*!< %Parameters of the algorithm */

    /**
     * Constructs the LBFGS algorithm with the input objective function
     * \param[in] objectiveFunction Objective function that can be represented as a sum of functions
     */
    Batch(sum_of_functions::BatchPtr objectiveFunction = sum_of_functions::BatchPtr()) :
        iterative_solver::Batch(),
        parameter(objectiveFunction)
    {
        initialize();
    }

    /**
     * Constructs an LBFGS algorithm by copying input objects of another LBFGS algorithm
     * \param[in] other An algorithm to be used as the source to initialize the input objects
     *                  and parameters of the algorithm
     */
    Batch(const Batch<algorithmFPType, method> &other) :
        iterative_solver::Batch(other),
        input(other.input),
        parameter(other.parameter)
    {
        initialize();
        input.set(iterative_solver::inputArgument, other.input.get(iterative_solver::inputArgument));
        input.set(iterative_solver::optionalArgument, other.input.get(iterative_solver::optionalArgument));
    }

    /**
     * Returns method of the algorithm
     * \return Method of the algorithm
     */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int) method; }

    /**
     * Creates user-allocated memory to store results of the iterative solver algorithm
     */
    virtual void createResult() DAAL_C11_OVERRIDE
    {
        _result = services::SharedPtr<iterative_solver::Result>(new Result());
        _res = NULL;
    }

    /**
     * Returns a pointer to the newly allocated LBFGS algorithm with a copy of input objects
     * of this LBFGS algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

protected:
    virtual Batch<algorithmFPType, method> *cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, method>(*this);
    }

    virtual void allocateResult() DAAL_C11_OVERRIDE
    {
        static_cast<Result*>(_result.get())->allocate<algorithmFPType>(&input, &parameter, (int)method);
        _res = _result.get();
    }

    void initialize()
    {
        iterative_solver::Batch::parameter = &parameter;
        Analysis<batch>::_ac = new __DAAL_ALGORITHM_CONTAINER(batch, BatchContainer, algorithmFPType, method)(&_env);
        _par = &parameter;
        _in  = &input;
        iterative_solver::Batch::input = &input;
        _result = services::SharedPtr<Result>(new Result());
    }
};
/** @} */
} // namespace interface1
using interface1::BatchContainer;
using interface1::Batch;

} // namespace lbfgs
} // namespace optimization_solver
} // namespace algorithm
} // namespace daal

#endif
