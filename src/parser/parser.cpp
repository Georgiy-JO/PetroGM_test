#include "parser.h"
#include "hline.h"
#include "point.h"
#include "rect.h"
#include "vline.h"
#include <fstream>
#include <sstream>

namespace parser {
using namespace scene;

Parser::Parser(const std::string &file_path) : m_file_path(file_path) {}

void Parser::SetFilePath(const std::string &file_path) {
  m_file_path = file_path;
}

const std::string &Parser::GetFilePath() const { return m_file_path; }

void Parser::Parse(Scene &scene) const {
  if (m_file_path.empty())
    throw std::runtime_error("Error! Filename is not set.");
  std::ifstream file(m_file_path);
  if (!file)
    throw std::runtime_error("Error! File can't be opened.");
  std::string line;
  if (!std::getline(file, line))
    throw std::runtime_error("Error! Empty file.");

  std::istringstream iss(line);
  float x1, y1, x2, y2;
  if (!(iss >> x1 >> y1 >> x2 >> y2))
    throw std::runtime_error("Error! Invalid borders data.");
  scene.SetBorders(Vec2(x1, y1), Vec2(x2, y2));

  while (std::getline(file, line)) {
    auto obj = CreateObjectFromLine(line);
    if (obj) {
      scene.AddObject(std::move(obj));
    }
  }
}

void Parser::Parse(const std::string &input_file, scene::Scene &scene) {
  SetFilePath(input_file);
  Parse(scene);
}

std::unique_ptr<Object>
Parser::CreateObjectFromLine(const std::string &line) const {
  std::istringstream iss(line);
  std::string type;
  iss >> type;
  if (type == "point") {
    float x, y;
    if (iss >> x >> y)
      return std::make_unique<Point>(Vec2(x, y));
  } else if (type == "rect") {
    float x1, y1, x2, y2;
    if (iss >> x1 >> y1 >> x2 >> y2)
      return std::make_unique<Rect>(Vec2(x1, y1), Vec2(x2, y2));
  } else if (type == "hline") {
    float x1, x2, y;
    if (iss >> x1 >> x2 >> y)
      return std::make_unique<HLine>(x1, x2, y);
  } else if (type == "vline") {
    float y1, y2, x;
    if (iss >> y1 >> y2 >> x)
      return std::make_unique<VLine>(x, y1, y2);
    // } else if (type == "circle") {  // Custom type
    //     float x, y, r; iss >> x >> y >> r; return std::make_unique<Circle>(x,
    //     y, r);
    // } else if (type == "triangle") {  // Custom type (outline for now)
    //     float x1, y1, x2, y2, x3, y3; iss >> x1 >> y1 >> x2 >> y2 >> x3 >>
    //     y3; return std::make_unique<Triangle>(x1, y1, x2, y2, x3, y3);
  }
  return nullptr;
}
} // namespace parser