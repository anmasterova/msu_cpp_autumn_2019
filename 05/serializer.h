/*Serializer*/

#include <sstream>


enum class Error
{
    NoError,
    CorruptedArchive
};



class Serializer
{
    static constexpr char Separator = ' '; 

public:

    explicit Serializer(std::ostream& out) : out_(out) {}

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    
private:
    // process использует variadic templates
    std::ostream& out_;

    template <class T, class... ArgsT>
    Error process(T&& arg, ArgsT&&... args)
    {
        write(arg);
        return process(std::forward<ArgsT>(args)...);
    }

    template <class T>
    Error process(T&& arg)
    {
        write(arg);
        return Error::NoError;
    }
    
    void write(uint64_t arg)
    {
        out_ << arg << Separator;
    }

    void write(bool arg)
    {
        out_ << (arg ? "true" : "false") << Separator;
    }
};



class Deserializer
{
    static constexpr char Separator = ' ';

public:
    
    explicit Deserializer(std::istream& in) : in_(in) {}

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    
private:
    
    std::istream& in_;

    template <class T, class... ArgsT>
    Error process(T&& value, ArgsT&&... args)
    {
        if (load(value) == Error::CorruptedArchive)
            return Error::CorruptedArchive;
        else
            return process(std::forward<ArgsT>(args)...);
    }

    template <class T>
    Error process(T&& value)
    {
        return load(value);
    }
    
    Error load(uint64_t& value)
    {
        std::string text;
        in_ >> text;

        if (text.empty())  
            return Error::CorruptedArchive;
        
        for (size_t i = 0; i < text.length(); i++)
            if (!std::isdigit(text[i]))
                return Error::CorruptedArchive;
        value = std::stoull(text);
        
        return Error::NoError;
    }

    Error load(bool& value)
    {
        std::string text;            
        in_ >> text;
        
        if (text.empty())  
            return Error::CorruptedArchive;
        
        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;
        
        return Error::NoError;
    }
};
