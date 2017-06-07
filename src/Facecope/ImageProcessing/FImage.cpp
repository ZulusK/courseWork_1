//
// Created by Danil Kazimirov on 05.06.17.
//

#include "opencv2/imgproc.hpp"
#include <FFaceArea.h>
#include <FImage.h>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

FImage::FImage(const cv::Mat &image) {
  this->originalImage = image;
  this->is_persons_detected = false;
  this->is_persons_recognized = false;
}

FImage::FImage(const std::string &filePath) {
  this->originalImage = imread(filePath);
  this->is_persons_detected = false;
  this->is_persons_recognized = false;
}

FImage::~FImage() {
  clear();
  this->originalImage.release();
}

void FImage::add_face(FFaceArea &face) {
  // add face at the end of list
  this->detectedFaces.push_back(&face);
  face.set_areaID(this->detectedFaces.size() - 1);
  face.set_parent(*this);
}

void FImage::set_detected_status(bool status) {
  this->is_persons_detected = status;
}

void FImage::set_recognized_status(bool status) {
  this->is_persons_recognized = status;
}

bool FImage::is_detected() { return is_persons_detected; }

bool FImage::is_recognized() { return is_persons_recognized; }

void FImage::add_face(const std::vector<FFaceArea *> &faces) {
  for (auto it = faces.begin(); it != faces.end(); it++) {
    add_face(**it);
  }
}

FFaceArea *FImage::get_face(long id) {
  if (id < detectedFaces.size()) {
    return this->detectedFaces[id];
  } else {
    return NULL;
  }
}

std::vector<FFaceArea *> FImage::get_faces() { return this->detectedFaces; }

bool FImage::remove_face(long id) {
  if (id < detectedFaces.size()) {
    // free mem
    delete detectedFaces[id];
    // swap last object
    detectedFaces[id] = *(detectedFaces.end() - 1);
    detectedFaces[id]->set_areaID(id);
    detectedFaces.erase(detectedFaces.end() - 1);
    return true;
  } else {
    return false;
  }
}

void FImage::clear() {
  for (auto it = detectedFaces.begin(); it != detectedFaces.end(); it++) {
    delete *it;
  }
  detectedFaces.clear();
}

const cv::Mat &FImage::get_image() const { return this->originalImage; }

bool FImage::empty() { return originalImage.empty(); }

Size FImage::get_size() {
  return Size(originalImage.cols, originalImage.rows);
}
