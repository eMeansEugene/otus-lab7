//
// Created by evgen on 27.08.2026.
//

#include "accumulator.h"

Accumulator::Accumulator(const size_t N): block_size_(N) {
}

void Accumulator::AddObserver(const std::shared_ptr<IObserver>& os) {
    observers_.push_back(os);
}

void Accumulator::ProcessCommand(const std::string& command) {
    if (command == "{") {
        HandleOpenBrace();
    } else if (command == "}") {
        HandleCloseBrace();
    } else {
        HandleCommand(command);
    }
}

void Accumulator::HandleOpenBrace() {
    if (dynamic_depth_ == 0) {
        FlushStaticBlockIfAny();
        block_start_time_ = 0;
    }
    ++dynamic_depth_;
}

void Accumulator::HandleCloseBrace() {
    if (dynamic_depth_ == 0) {
        return;
    }
    --dynamic_depth_;
    if (dynamic_depth_ == 0 && !current_block_.empty()) {
        NotifyObservers();
        current_block_.clear();
    }
}

void Accumulator::HandleCommand(const std::string& command) {
    if (current_block_.empty()) {
        block_start_time_ = time(nullptr);
    }
    current_block_.emplace_back(command);
    if (dynamic_depth_ == 0 && current_block_.size() == block_size_) {
        NotifyObservers();
        current_block_.clear();
    }
}

void Accumulator::HandleEof() {
    if (dynamic_depth_ == 0) {
        FlushStaticBlockIfAny();
    } else {
        current_block_.clear();
    }
    dynamic_depth_= 0;
}

void Accumulator::NotifyObservers() const {
    for (const auto& os : observers_) {
        os->OnBlockComplete(current_block_, block_start_time_);
    }
}


void Accumulator::FlushStaticBlockIfAny() {
    if (!current_block_.empty()) {
        NotifyObservers();
    }
    current_block_.clear();
}
