#pragma once
#include<iostream>
#include<exception>
#include<string>

class PixelError : public std::exception {
	std::string err = "Pixel value is not valid (value must be between 0 and 255)";
public:
	PixelError(std::string e) : err(e) {}
	PixelError() = default;
	const char* what()const override {
		return err.c_str();
	}
};
class LayerError : public std::exception {
	std::string err = "Error";
public:
	LayerError(std::string e) : err(e) {}
	LayerError() = default;
	const char* what()const override {
		return err.c_str();
	}
};

class FileError : public std::exception {
	std::string err = "Unable to open a file";
public:
	FileError(std::string e) : err(e) {}
	FileError() = default;
	const char* what()const override {
		return err.c_str();
	}
};

class SelectionError : public std::exception {
	std::string err = "Selection does not exist";
public:
	SelectionError(std::string e) : err(e) {}
	SelectionError() = default;
	const char* what()const override {
		return err.c_str();
	}
};

