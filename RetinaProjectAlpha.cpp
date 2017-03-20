// RetinaProjectAlpha.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

enum class ConeType {
	RED,
	GREEN,
	BLUE,
};

enum class BipolarType {
	ON,
	OFF,
};

class Neuron {
private:
	float cellPotential;
	bool isGraded;
	std::vector<Neuron> inputConnectedCells;
	std::vector<Neuron> outputConnectedCells;

public:
	Neuron() {
		cellPotential = -40;
		isGraded = false;
	}

	Neuron(float potential) {
		cellPotential = potential;
		isGraded = false;
	}

	Neuron(float potential, bool graded) {
		cellPotential = potential;
		isGraded = graded;
	}

	std::vector<std::vector<float>> acquireInputs() {
		std::vector<float> potentials = std::vector<float>{};
		for (int i = 0; i < inputConnectedCells.size(); ++i) {
			potentials.resize(i + 1);
			potentials[i] = inputConnectedCells[i].getPotential();
		}

		return std::vector<std::vector<float>> {potentials};
	}

	void update(int ticks){
		acquireInputs();
		//Do whatever calculation is neccesary to obtain a cell potential.
		//cellPotential = evaluated value;
	}

	float getPotential() {
		return cellPotential;
	}
};

class Photoreceptor : public Neuron{
private:
	//float eccentricity;
	//float locationAngle; //Relative to straight up
public:
	Photoreceptor() : Neuron(-40, true) {}

	virtual void setInputs(int lightIntensity, int lightFrequency, int lightAngle) {

	}

	float getPotential() {

	}
};

class Cone : public Photoreceptor {
private:
	ConeType coneType;

public:
	static constexpr float PEAK_DENSITY() { return 199.2; }
	static constexpr float PERIPHERY_DENSITY() { return 3.6; }
	static constexpr float MEAN_DENSITY_CONSTANT() { return 15; } //Ignore these for now

	Cone(ConeType t) {
		coneType = t;
	}

	void setInputs(int lightIntensity, int lightFrequency, int lightAngle) {
		//TODO: Actually do something with this
	}
};

class Rod : public Photoreceptor {
	void setInputs(int lightIntensity, int lightFrequency, int lightAngle) {
		//TODO: Actually so something with this too
	}
};

//When generated, use distance from retinal center to compute receptive field size/distance between receptive fields.
class Bipolar : public Neuron {
private:
	BipolarType type;
	std::vector<Neuron> inputCenterCells;
	std::vector<Neuron> inputSurroundCells;

public:
	Bipolar(BipolarType t) : Neuron(-40 /*Not sure what this number is for the bipolar cells*/, true) { type = t; }

	std::vector<std::vector<float>> acquireInputs() {
		std::vector<std::vector<float>> potentials;
		for (int i = 0; i < inputCenterCells.size(); ++i) {
			potentials[0][i] = inputCenterCells[i].getPotential();
		}
		for (int i = 0; i < inputSurroundCells.size(); ++i) {
			potentials[1][i] = inputSurroundCells[i].getPotential();
		}
	}
};

class Ganglion : public Neuron {
public:
	Ganglion() {}
};

//float receptorDensity(bool isCone, float ecc) {
//	float returnValue;
//	if (isCone) {
//		returnValue = (Cone::PEAK_DENSITY() - Cone::PERIPHERY_DENSITY())/(Cone::MEAN_DENSITY_CONSTANT()*ecc + 1) + Cone::PERIPHERY_DENSITY();
//	}
//	else {
//		returnValue = (-0.0001395*ecc*ecc + 1.13) * 176 * 3.6/ ((Cone::PEAK_DENSITY() - Cone::PERIPHERY_DENSITY()) / (Cone::MEAN_DENSITY_CONSTANT()*ecc + 1) + Cone::PERIPHERY_DENSITY());
//	}
//
//	return returnValue;
//}

int main()
{
	std::vector<Photoreceptor> receptors;
	std::vector<Bipolar> bipolars;
	std::vector<Ganglion> ganglia;

	
}

