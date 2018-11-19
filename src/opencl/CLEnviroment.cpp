#include "CLEnviroment.h"
#include "../auxiliary/aux.h"
#include <iostream>
#include <stdexcept>
#include <vector>


CLEnviroment::CLEnviroment() {
	// Get platform
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get (&all_platforms);
	if (all_platforms.empty ()) {
		throw std::runtime_error ("No OpenCL platforms found");
	}
	platform = all_platforms.at(0);
	std::cout << "OpenCL platform: " << platform.getInfo<CL_PLATFORM_NAME>() << std::endl;

	// Get device
	std::vector<cl::Device> all_devices;
	platform.getDevices (CL_DEVICE_TYPE_ALL, &all_devices);
	if (all_devices.empty ()) {
		throw std::runtime_error ("No OpenCL devices found");
	}
	device = all_devices.at(0);
	std::cout << "Device: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;

	// Create context and queue
	context = cl::Context ({device});
	cmd_queue = cl::CommandQueue (context, device);
}


CLProgram::CLProgram (const CLEnviroment &env, const std::string &path) {
	// Load code
	auto[src_str, success] = aux::loadFileToString (path);
	if (!success)
		throw std::runtime_error ("Can't find file " + path);
	src.push_back ({src_str.c_str (), src_str.length ()});
	std::cout << path << " loaded" << std::endl;

	// Build program
	prog = cl::Program (env.ctx(), src);
	if (prog.build ({env.dev ()}) != CL_SUCCESS) {
		throw std::runtime_error ("Error building a program: " +
		                          prog.getBuildInfo<CL_PROGRAM_BUILD_LOG> (env.dev ()) + "\n");
	}
	std::cout << path << " compiled" << std::endl;
}
