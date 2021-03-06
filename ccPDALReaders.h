#ifndef CLOUDCOMPAREPROJECTS_CCPDALREADERS_H
#define CLOUDCOMPAREPROJECTS_CCPDALREADERS_H

#include <pdal/Reader.hpp>
#include <pdal/Streamable.hpp>


#include <ccPointCloud.h>


class ccPointCloudStreamReader : public pdal::Reader, pdal::Streamable {
public:
	ccPointCloudStreamReader(ccPointCloud *mCloud) : m_cloud(mCloud)
	{}

	std::string getName() const override
	{
		return "readers.ccPointCloudStreamReader";
	}

private:
	void addDimensions(pdal::PointLayoutPtr ptr) override
	{
		ptr->registerDim(pdal::Dimension::Id::X);
		ptr->registerDim(pdal::Dimension::Id::Y);
		ptr->registerDim(pdal::Dimension::Id::Z);
	}

private:
	bool processOne(pdal::PointRef &point) override
	{
		const CCVector3 *ccPoint = m_cloud->getPoint(m_currentPoint);
		point.setField(pdal::Dimension::Id::X, ccPoint->x);
		point.setField(pdal::Dimension::Id::Y, ccPoint->y);
		point.setField(pdal::Dimension::Id::Z, ccPoint->z);
		m_currentPoint++;
		return m_currentPoint < m_cloud->size();
	}

private:
	ccPointCloud *m_cloud;
	unsigned m_currentPoint = 0;
};


#endif //CLOUDCOMPAREPROJECTS_CCPDALREADERS_H
