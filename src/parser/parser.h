#pragma once

#include "scene.h"
#include <memory>
#include <string>

namespace parser {

class Parser {
public:
  Parser() = default;
  Parser(const std::string &file_path);
  ~Parser() = default;

  void SetFilePath(const std::string &file_path);
  const std::string &GetFilePath() const;

  void Parse(scene::Scene &scene) const;
  void Parse(const std::string &file_path, scene::Scene &scene);

private:
  std::unique_ptr<scene::Object>
  CreateObjectFromLine(const std::string &line) const;

  std::string m_file_path;
};
} // namespace parser