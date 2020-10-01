#include "chrono_synchrono/visualization/SynSensorVisualization.h"

#include "chrono_sensor/ChCameraSensor.h"
#include "chrono_sensor/ChLidarSensor.h"
#include "chrono_sensor/Sensor.h"

namespace chrono {
namespace synchrono {

SynSensorVisualization::SynSensorVisualization()
    : SynVisualization(SynVisualization::SENSOR), m_needs_reconstruction(true) {}

// SynSensorVisualization::SynSensorVisualization(const std::string& filename)
//     : SynVisualization(SynVisualization::SENSOR) {
//     m_sensor = Sensor::CreateFromJSON(filename);
// }

void SynSensorVisualization::Update(double step) {
    if (m_needs_reconstruction) {
        m_sensor_manager->ReconstructScenes();
        m_needs_reconstruction = false;
    }
    m_sensor_manager->Update();
}

void SynSensorVisualization::Initialize() {
    if (m_sensor_manager == nullptr) {
        std::cout
            << "SynSensorVisualization::Initialize: Sensor manager has not been initialized. Must initialize prior "
               "to adding sensor. Exitting..."
            << std::endl;
        exit(-1);
    } else if (m_sensor == nullptr) {
        // std::cout
        //     << "SynSensorVisualization::Initialize: Sensor has not been created or attached. Must attach a sensor
        //     prior "
        //        "to initializing the sensor vis. Exitting..."
        //     << std::endl;
        // exit(-1);
        return;
    }
    m_sensor_manager->AddSensor(m_sensor);
}

void SynSensorVisualization::InitializeDefaultSensorManager(ChSystem* system) {
    if (m_sensor_manager == nullptr) {
        // create the sensor manager and a camera
        m_sensor_manager = chrono_types::make_shared<ChSensorManager>(system);

        // add default lights
        m_sensor_manager->scene->AddPointLight({100, 100, 100}, {1, 1, 1}, 5000);
        m_sensor_manager->scene->AddPointLight({-100, -100, 100}, {1, 1, 1}, 5000);
    } else {
        std::cerr << "SensorVisualizationTypeManager::InitializeDefaultSensorManager: Sensor manager has already been "
                     "initialized. "
                     "Ignoring..."
                  << std::endl;
    }
}

void SynSensorVisualization::InitializeAsDefaultChaseCamera(std::shared_ptr<ChBodyAuxRef> body_ref,
                                                            unsigned int width,
                                                            unsigned int height,
                                                            float fps,
                                                            std::string window_title) {
    m_sensor = chrono_types::make_shared<ChCameraSensor>(
        body_ref,                                                                      // body camera is attached to
        fps,                                                                           // update rate in Hz
        chrono::ChFrame<double>({20, 0, 3}, Q_from_AngAxis(CH_C_PI, {0, 0, 1})),  // offset pose
        width,                                                                         // image width
        height,                                                                        // image height
        CH_C_PI / 3);                                                                  // horizontal field of view
    m_sensor->SetLag(1 / fps);
    m_sensor->SetName(window_title);
}

void SynSensorVisualization::InitializeAsDefaultBirdsEyeCamera(std::shared_ptr<ChBodyAuxRef> body_ref,
                                                               double z,
                                                               unsigned int width,
                                                               unsigned int height,
                                                               float fps,
                                                               std::string window_title) {
    m_sensor = chrono_types::make_shared<ChCameraSensor>(
        body_ref,                                                                     // body camera is attached to
        fps,                                                                          // update rate in Hz
        chrono::ChFrame<double>({0, 0, z}, Q_from_AngAxis(CH_C_PI / 2., {0, 1, 0})),  // offset pose
        width,                                                                        // image width
        height,                                                                       // image height
        CH_C_PI / 3);                                                                 // horizontal field of view
    m_sensor->SetLag(1 / fps);
    m_sensor->SetName(window_title);
}

void SynSensorVisualization::AddFilterRGBA8Access() {
    auto camera = std::static_pointer_cast<ChCameraSensor>(m_sensor);
    if (camera) {
        camera->PushFilter(chrono_types::make_shared<ChFilterRGBA8Access>());
    } else {
        std::cout << "SynSensorVisualization::AddFilterRGBA8Access: Attached sensor is not a camera. Ignoring..."
                  << std::endl;
    }
}

void SynSensorVisualization::AddFilterVisualize(unsigned int w, unsigned int h) {
    auto camera = std::static_pointer_cast<ChCameraSensor>(m_sensor);
    if (camera) {
        camera->PushFilter(chrono_types::make_shared<ChFilterVisualize>(w, h));
        return;
    }
    auto lidar = std::static_pointer_cast<ChLidarSensor>(m_sensor);
    if (lidar) {
        lidar->PushFilter(chrono_types::make_shared<ChFilterVisualize>(w, h));
        return;
    }
    std::cout << "SynSensorVisualization::AddFilterVisualize: Attached sensor is not a camera or a lidar. Ignoring..."
              << std::endl;
}

void SynSensorVisualization::AddFilterSave(std::string file_path) {
    auto camera = std::static_pointer_cast<ChCameraSensor>(m_sensor);
    if (camera) {
        camera->PushFilter(chrono_types::make_shared<ChFilterSave>(file_path));
        return;
    }
    auto lidar = std::static_pointer_cast<ChLidarSensor>(m_sensor);
    if (lidar) {
        lidar->PushFilter(chrono_types::make_shared<ChFilterSave>(file_path));
        return;
    }
    std::cout << "SynSensorVisualization::AddFilterSave: Attached sensor is not a camera or a lidar. Ignoring..."
              << std::endl;
}
}  // namespace synchrono
}  // namespace chrono