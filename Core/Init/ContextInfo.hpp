#ifndef CONTEXTINFO_H
#define CONTEXTINFO_H

struct ContextInfo {
  int major_version, minor_version;
  bool core;

  ContextInfo(){
    major_version = 4;
    minor_version = 3;
    core = true;
  }

  ContextInfo(int major, int minor, bool c)
    : major_version{major}, minor_version{minor}, core{c} {}

  ContextInfo(const ContextInfo& contextInfo) = default;
  ContextInfo& operator=(const ContextInfo& contextInfo) = default;
};

#endif
