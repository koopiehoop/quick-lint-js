// Copyright (C) 2020  Matthew "strager" Glazar
// See end of file for extended copyright information.

#ifndef QUICK_LINT_JS_FILE_H
#define QUICK_LINT_JS_FILE_H

#include <quick-lint-js/char8.h>
#include <quick-lint-js/file-handle.h>
#include <quick-lint-js/padded-string.h>
#include <string>

namespace quick_lint_js {
struct read_file_result {
  padded_string content;
  std::string error;
  bool is_not_found_error = false;

  bool ok() const noexcept { return this->error.empty(); }
  void exit_if_not_ok() const;

  static read_file_result failure(const std::string &error);
};

read_file_result read_file(const char *path);

read_file_result read_file(const char *path, platform_file_ref);

read_file_result read_stdin(void);

void write_file(const std::string &path, string8_view content);
void write_file(const char *path, string8_view content);

class canonical_path_result {
 public:
  explicit canonical_path_result(const char *path);

  std::string_view path() const &noexcept;
  std::string &&path() && noexcept;
  const char *c_str() const noexcept;

  std::string &&error() && noexcept;

  bool ok() const noexcept { return this->error_.empty(); }

  static canonical_path_result failure(std::string &&error);

 private:
  explicit canonical_path_result();

  std::string path_;
  std::string error_;
};

canonical_path_result canonicalize_path(const char *path);
canonical_path_result canonicalize_path(const std::string &path);
}

#endif

// quick-lint-js finds bugs in JavaScript programs.
// Copyright (C) 2020  Matthew "strager" Glazar
//
// This file is part of quick-lint-js.
//
// quick-lint-js is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// quick-lint-js is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with quick-lint-js.  If not, see <https://www.gnu.org/licenses/>.
