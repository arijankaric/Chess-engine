#include <material.hpp>

Material::Material() = default;
Material::Material(int file, int rank, bool colored) : file_{file}, rank_{rank}, colored_{colored} {}
Material::~Material() = default;