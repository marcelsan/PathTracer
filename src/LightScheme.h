#ifndef LIGHT_SCHEME_H
#define LIGHT_SCHEME_H

#include "Light.h"
#include "Vec.h"
#include <vector>

class LightScheme
{
	private:
		float ambientIntensity;
		Color ambientColor;
		std::vector<Light> lights;
		
	public:
		LightScheme() {}
		LightScheme(float ambientIntensity, Color ambientColor) : ambientIntensity(ambientIntensity), ambientColor(ambientColor), selectedLight(0) {}
		
		void setAmbientIntensity(float ambientIntensity)
		{
			if(ambientIntensity >= 0 && ambientIntensity <= 1)
				this->ambientIntensity = ambientIntensity;
			else
				this->ambientIntensity = 1.0;
		}

		void setAmbientColor(Color ambientColor)
		{
			this->ambientColor = ambientColor;
		}

		void add(Light light)
		{
			this->lights.push_back(light);
		}

		const Vec4f getNormalizedAmbient() const
		{
			float sum = this->ambientColor.data[0] + this->ambientColor.data[1] + this->ambientColor.data[2];

			float r = this->ambientColor.data[0]/sum;
			float g = this->ambientColor.data[1]/sum;
			float b = this->ambientColor.data[2]/sum;

			return Vec4f(r,g,b, this->ambientIntensity);
		}

		const std::vector<Light>& getLights() const
		{
			return lights;
		}

};

#endif 