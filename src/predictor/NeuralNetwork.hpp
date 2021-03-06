/*
 * =====================================================================================
 *
 *       Filename:  NeuralNetwork.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/04/2015 06:20:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <utility>
#include <vector>
#include <stdio.h>

#include <shogun/io/CSVFile.h>
#include <shogun/base/init.h>
#include <shogun/mathematics/Math.h>

#include <shogun/features/DenseFeatures.h>
#include <shogun/labels/MulticlassLabels.h>
#include <shogun/labels/RegressionLabels.h>
#include <shogun/evaluation/MulticlassAccuracy.h>

#include <shogun/neuralnets/NeuralNetwork.h>
#include <shogun/neuralnets/NeuralLayers.h>
#include "src/predictor/functions.hpp"

#include <shogun/multiclass/tree/CARTree.h>


template <typename F, typename L> 
class NeuralNetwork 
{
	public:
		using Features = F;
		using Labels = L;
		using Sample = std::pair<F, L>;

		NeuralNetwork() {
//			shogun::init_shogun();
//			shogun::init_shogun(&print_message, &print_warning, &print_error);
		}

		~NeuralNetwork() {
			SG_UNREF(m_train_dfeats);
			SG_UNREF(m_train_dlabels);
			SG_UNREF(m_network);
//			exit_shogun();
		}

		static void init() {
//			shogun::init_shogun();
			shogun::init_shogun(&print_message, &print_warning, &print_error);
		}

		Labels predict(const Features& features);
		std::vector<Labels> predict(const std::vector<Features>& features);
		void open(const std::string& filename);
		int train();
		void evaluate();

	private:
		shogun::CDenseFeatures<float64_t>* m_train_dfeats;
//		shogun::CMulticlassLabels* m_train_dlabels;
		shogun::CRegressionLabels* m_train_dlabels;
		shogun::CNeuralLayers* layers;
		shogun::CNeuralNetwork* m_network;
};


template <typename F, typename L> 
void NeuralNetwork<F, L>::open(const std::string& filename) {
	using namespace shogun;
	using namespace std;

	CCSVFile* file = new CCSVFile(filename.c_str());	
	SGMatrix<float64_t> samples;
	samples.load(file);
	SG_UNREF(file);

	SGMatrix<float64_t> train_feats(samples.num_rows - 1, samples.num_cols);
	SGVector<float64_t> train_labels(samples.num_cols);

	const int32_t nrows = samples.num_rows;
	const int32_t ncols = samples.num_cols;
	const int32_t n_tf_rows = train_feats.num_rows;

	for (int ncol = 0; ncol < ncols ; ncol++) {
		for (int nrow = 0; nrow < train_feats.num_rows ;  nrow++) {
			train_feats.matrix[ncol * n_tf_rows + nrow] = samples.matrix[ncol * nrows + nrow];
		}
	}

	for (int i = 0; i < train_labels.size(); i++) {
		train_labels[i] = samples.matrix[i * samples.num_rows + samples.num_rows - 1];
	}

	normalize(train_feats);

	float64_t max_value;
	max_value = CMath::max(train_labels.vector, train_labels.vlen);
	SGVector<float64_t>::scale_vector(1 / max_value, train_labels.vector, train_labels.vlen);

//	cout << train_feats << endl;

	m_train_dfeats = new CDenseFeatures<float64_t>(train_feats);
//	m_train_dlabels = new CMulticlassLabels(train_labels);
	m_train_dlabels = new CRegressionLabels(train_labels);
}



template <typename F, typename L> 
int NeuralNetwork<F, L>::train() {
	using namespace shogun;
	using namespace std;

	#ifdef HAVE_LAPACK 
	// Create a small network single hidden layer m_network
	layers = new CNeuralLayers();
//	layers->input(m_train_dfeats->get_num_features())->logistic(10)->logistic(10)->softmax(1);
//	layers->input(m_train_dfeats->get_num_features())->linear(550)->linear(1);
//	layers->input(m_train_dfeats->get_num_features())->rectified_linear(15)->linear(1);
	layers->input(m_train_dfeats->get_num_features())->rectified_linear(150)->linear(1);
	m_network = new CNeuralNetwork(layers->done());
//	m_network->optimization_method = NNOM_GRADIENT_DESCENT;
	m_network->epsilon=0.0000005;

	// initialize the m_network
	m_network->quick_connect();
	m_network->initialize();

	// uncomment this line to enable info logging
	m_network->io->set_loglevel(MSG_INFO);

	// train using default parameters
	m_network->set_labels(m_train_dlabels);
	m_network->train(m_train_dfeats);

	// cleanup
	SG_UNREF(layers);
	#endif
	return 0;
}



template <typename F, typename L> 
void NeuralNetwork<F, L>::evaluate() {
	using namespace shogun;
	using namespace std;
//	CMulticlassLabels* predictions = m_network->apply_multiclass(m_train_dfeats);
	CRegressionLabels* predictions = m_network->apply_regression(m_train_dfeats);
//	CMulticlassAccuracy* evaluator = new CMulticlassAccuracy();
//	float64_t accuracy = evaluator->evaluate(predictions, m_train_dlabels);

	const size_t ncols = predictions->get_labels().size();

	for (size_t i = 0; i < ncols; i = i + 5) {
		cout << m_train_dlabels->get_labels()[i] << " : " << predictions->get_labels()[i] << endl;
	}

//	SG_SINFO("Accuracy = %f %\n", accuracy*100);
	SG_UNREF(predictions);
//	SG_UNREF(evaluator);
}



template <typename F, typename L> 
typename NeuralNetwork<F, L>::Labels NeuralNetwork<F, L>::predict(const Features& fv) {
	using namespace shogun;
	using namespace std;

	SGMatrix<float64_t> sg_feature_matrix(fv.size(), 10);
	for (size_t i = 0; i < fv.size(); i++) {
		sg_feature_matrix.matrix[i] = fv[i];
	}

	CDenseFeatures<float64_t>* df = new CDenseFeatures<float64_t>(sg_feature_matrix);
//	CMulticlassLabels* ml = m_network->apply_multiclass(df);
	CRegressionLabels* ml = m_network->apply_regression(df);
	SGVector<float64_t> values = ml->get_labels_copy();

	SG_UNREF(df);
	return values[0];
}



template <typename F, typename L> 
std::vector<typename NeuralNetwork<F, L>::Labels> NeuralNetwork<F, L>::predict(const std::vector<Features>& fv) {
	using namespace shogun;
	using namespace std;

	SGMatrix<float64_t> sg_feature_matrix = convert(fv);

	CDenseFeatures<float64_t>* df = new CDenseFeatures<float64_t>(sg_feature_matrix);
//	CMulticlassLabels* ml = m_network->apply_multiclass(df);
	CRegressionLabels* ml = m_network->apply_regression(df);
//	SGVector<float64_t> values = ml->get_labels_copy();

	SG_UNREF(df);
	
	SGVector<float64_t> rlabels = ml->get_labels();	
	vector<Labels> x = convert(rlabels);
	return x;
}

#endif
