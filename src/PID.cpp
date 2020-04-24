#include "PID.h"

/**
 * PID class
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * Initialize PID coefficients 
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  
  // Initialize the errors
  d_error = 0.0;
  p_error = 0.0;
  i_error = 0.0;

}


void PID::UpdateError(double cte) {
  /**
   * Update PID errors based on cte.
   */
  d_error = cte - p_error;  // Calculate the difference before updating p_error
  p_error = cte;
  i_error = i_error+ cte ;  
}


double PID::TotalError() {
  /**
   * Calculate and return the total error
   */
  // Total error calculation
  
  double tot_error = -(Kp*p_error + Ki*i_error + Kd*d_error);
  
  return tot_error;  
}