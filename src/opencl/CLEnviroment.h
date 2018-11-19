#pragma once

#define CL_TARGET_OPENCL_VERSION 120
#include <CL/cl.hpp>
#include <string>


class CLEnviroment {
	cl::Platform platform;
	cl::Device device;
	cl::Context context;
	cl::CommandQueue cmd_queue;
public:
	CLEnviroment ();
	const cl::Context& ctx () const { return context; }
	const cl::Device& dev () const { return device; }
	const cl::CommandQueue& queue () const { return cmd_queue; }
};


class CLProgram {
	cl::Program prog;
	cl::Program::Sources src;
public:
	CLProgram (const CLEnviroment& env, const std::string& path);
	const cl::Program& program () const { return prog; }
};
