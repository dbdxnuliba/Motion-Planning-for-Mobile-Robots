#ifndef _TRAJECTORY_GENERATOR_WAYPOINT_H_
#define _TRAJECTORY_GENERATOR_WAYPOINT_H_

#include <eigen3/Eigen/Eigen>
#include <vector>

class TrajectoryGeneratorWaypoint {
public:
  TrajectoryGeneratorWaypoint();

  ~TrajectoryGeneratorWaypoint();

  /**
   * @brief get minimum num. of polynomial coeffs to satisfy [cOrder]th continuous constraints
   *
   * @param[in] cOrder continuity constraints, the target trajectory should be [cOrder]th continuous at intermediate waypoints
   *
   * @return minimum num of polynomial coeffs
   */
  static inline int GetNumCoeffs(const int cOrder) { return (cOrder + 1) << 1; }
  
  /**
   * @brief get partial factorial generated in derivative computing
   *
   * @param[in] N polynomial term power
   * @param[in] D derivative order
   *
   * @return partial factorial as N!/D!
   */
  static double GetFactorial(const int N, const int D);

  /**
   * @brief evaluate trajectory polynomial
   *
   * @param[in] N polynomial term power
   * @param[in] D derivative order
   *
   * @return result waypoint
   */
  static double EvaluatePoly(const Eigen::VectorXd &coeffs, const double t);

  /**
   * @brief generate minimum snap trajectory through numeric method with OSQP C++
   *
   * @param[in] tOrder the L2-norm of [tOrder]th derivative of the target trajectory will be used as objective function
   * @param[in] cOrder continuity constraints, the target trajectory should be [cOrder]th continuous at intermediate waypoints
   * @param[in] Pos equality constraints, the target trajectory should pass all the waypoints, (K + 1)-by-D
   * @param[in] Vel equality constraints, boundary(start & goal) velocity specifications, 2-by-D
   * @param[in] Acc equality constraints, boundary(start & goal) acceleration specifications, 2-by-D
   * @param[in] Time pre-computed time allocations, K-by-1
   *
   * @return polynomial coeffs of generated trajectory, K-by-(D * N)
   * @note the pre-assumption is no allocated segment time in Time is 0
   */
  Eigen::MatrixXd PolyQPGeneration(
    const int tOrder,
    const int cOrder,                    
    const Eigen::MatrixXd &Pos,
    const Eigen::MatrixXd &Vel,
    const Eigen::MatrixXd &Acc,
    const Eigen::VectorXd &Time
  );

private:
  /**
    * @brief generate minimum snap trajectory through numeric method with OSQP C++
    *
    * @param[in] tOrder the L2-norm of [tOrder]th derivative of the target trajectory will be used as objective function
    * @param[in] cOrder continuity constraints, the target trajectory should be [cOrder]th continuous at intermediate waypoints
    * @param[in] Pos equality constraints, the target trajectory should pass all the waypoints, (K + 1)-by-3
    * @param[in] Vel equality constraints, boundary(start & goal) velocity specifications, 2-by-3
    * @param[in] Acc equality constraints, boundary(start & goal) acceleration specifications, 2-by-3
    * @param[in] Time pre-computed time allocations, K-by-1
    *
    * @return polynomial coeffs of generated trajectory, K-by-N
    * @note the pre-assumption is no allocated segment time in Time is 0
  */
  Eigen::MatrixXd PolyQPGenerationNumeric(
    const int tOrder,       
    const int cOrder,    
    const Eigen::VectorXd &Pos,
    const Eigen::VectorXd &Vel,
    const Eigen::VectorXd &Acc,
    const Eigen::VectorXd &Time
  );

  double _qp_cost;
  Eigen::MatrixXd _Q;
  Eigen::VectorXd _Px, _Py, _Pz;
};
        

#endif
