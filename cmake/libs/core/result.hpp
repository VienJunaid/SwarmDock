#pragma once

#include <string>
#include <utility>
#include <variant>

namespace swarmdock::core {
    struct Error {
        std::string message;
        static Error of(std::string msg) { return Error{std::move(msg)}; }
    };

    template <class T>
    class Result {
        public:
            static Result ok(T value) { return Result(std::move(value)); }
            static Result err(std::string message) { return Result(Error{std::move(message)}); }

            bool is_ok() const { return std::holds_alternative<T>(data_); }
            bool is_err() const { return std::holds_alternative<Error>(data_); }

            T& value() { return std::get<T>(data_); }
            const T& value() const { return std::get<T>(data_); }

            const Error& error() const { return std::get<Error>(data_); }

        private:
            std::variant<T, Error> data_;

            /*
                explicit tells the compilers 
                don't do this conversion automatically = only do it 
                if I clearly ask for it.

                implicit would mean that a compiler can automatically convert one type
                to another without you asking. 
            */
            explicit Result(T v) : data_(std::move(v)) {}
            explicit Result(Error e) : data_(std::move(e)) {}



    };
} // namespace swarmdock::core 