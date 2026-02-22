#pragma once

#include "parser.h"
#include "scene.h"
#include <string>

/**
 * @brief This function wraps Parser and Scene together.
 * @note Не самая удачная структура классов была выбрана, но, к сожалению,
 * на наведение порядка не осталось времени.
 */
void SimpleBMP(const std::string &input_file, const std::string &output_file) {
  parser::Parser prs(input_file);
  scene::Scene scene;
  prs.Parse(scene);
  scene.RenderToBMP(output_file);
}