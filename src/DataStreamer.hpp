//
// Created by Ryan Elliott on 8/14/20.
//

#ifndef SUCCESSOR_DATASTREAMER_HPP
#define SUCCESSOR_DATASTREAMER_HPP


#include <ludere/IDataStreamer.hpp>
#include <fstream>

class DataStreamer : public lud::IDataStreamer
{
public:
    explicit DataStreamer(std::string filename)
            : m_filename(std::move(filename)), m_file(std::ifstream(m_filename))
    {}

    explicit DataStreamer(std::string_view filename)
            : m_filename(filename), m_file(std::ifstream(m_filename))
    {}

    std::unordered_map<std::string, lud::CandlestickData> pollNextStream() override
    {
        lud::CandlestickData candle;
        if (m_file >> candle) {
            return std::unordered_map<std::string, lud::CandlestickData>{std::make_pair(candle.ticker, candle) };
        }
        return std::unordered_map<std::string, lud::CandlestickData>{};
    }

private:
    const std::string m_filename;
    std::ifstream m_file;
};


#endif //SUCCESSOR_DATASTREAMER_HPP
