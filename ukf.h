#ifndef UKF_H
#define UKF_H

#include "global_settings.h"
#include <Eigen/Dense>
#include "state.h"
#include "measurement.h"
#include "merge.h"
#include "model.h"

class ukf {

	protected:
	bool _initialized;
	bool _debug;
	double _t;
	double _nis;
	double _llh;
	vector<double> _noises;

	VectorXd _x;
	MatrixXd _P;
	VectorXd _predicted_z;
	MatrixXd _S;
	MatrixXd _sigma_x;
	MatrixXd _sigma_z;

	measurement_predict _measurer;
	merger _merger;

	public:
	ukf();
	void initialize(ALL_DATA, double t, int NSIGMA, int NAUG, double W, double W0_m, double W0_c, vector<double> noises, double SCALE,
					ALL_VAR, model* m, bool debug);
	void process(ALL_DATA, double t, const VectorXd& imm_x, const MatrixXd& imm_P);
	void update(ALL_DATA, const VectorXd& imm_x, const MatrixXd& imm_P);
	void predict(double t, const VectorXd& imm_x, const MatrixXd& imm_P);
	VectorXd peek(double dt);
	VectorXd get() const;
	MatrixXd get_P() const;
	double get_nis() const;
	double get_llh() const;
	double get_measurement_pred(int no) const;
	double get_state_var(int i, int j);
	double get_noise(int i) const;
	virtual state_predict& get_stater();
};

#endif
