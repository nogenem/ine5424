#ifndef register_message_h__
#define register_message_h__

#include "../objects/smartobject.h"

using namespace EPOS;

namespace IoT {

    class RegisterMessage
    {
    public:
        typedef unsigned char Size;
        typedef SmartObject::ID ID;
        typedef unsigned char Type;

        enum
        {
            UNKNOWN_MESSAGE                 = 0,
            FIRST_TYPE                      = 1,

            REGISTER_REQUEST                = FIRST_TYPE,
            REGISTER_RESPONSE               = 2,
            REGISTER_OBJECT_REQUEST         = 3,
            REGISTER_OBJECT_RESPONSE        = 4,
            REGISTER_SERVICE_REQUEST        = 5,
            REGISTER_SERVICE_RESPONSE       = 6,
            REGISTER_PARAMETER_REQUEST      = 7,
            REGISTER_PARAMETER_RESPONSE     = 8,
            REGISTER_OPTION_REQUEST         = 9,
            REGISTER_OPTION_RESPONSE        = 10,
            REGISTER_END_OBJECT_REQUEST     = 11,
            REGISTER_END_OBJECT_RESPONSE    = 12,

            LAST_TYPE                       = REGISTER_END_OBJECT_RESPONSE
        } ;
        static const char START_CHAR = ';';
        static const Size BASE_SIZE = sizeof (START_CHAR ) + sizeof (Size ) + sizeof (ID )
        + sizeof (Type );
        static const Size MTU = IEEE802_15_4::Frame::MTU - BASE_SIZE;
    protected:
        Size _size;
        ID _id;
        Type _type;
    public:

        RegisterMessage ( )
        : _size ( BASE_SIZE ), _type ( UNKNOWN_MESSAGE ) {
            _id = *( ( ID* ) & Machine::id ( )[4] );
        }

        RegisterMessage ( Type type )
        : _size ( BASE_SIZE ), _type ( type ) {
            _id = *( ( ID* ) & Machine::id ( )[4] );
        }

        RegisterMessage ( Size messageSize, Type type )
        : _size ( BASE_SIZE + messageSize ), _type ( type ) {
            assert ( _size <= MTU );
            _id = *( ( ID* ) & Machine::id ( )[4] );
        }

        Size getSize ( ) {
            return _size;
        }

        void setSize ( Size size ) {
            _size = size;
            assert ( _size <= MTU );
        }

        void setSizeAddedWithBaseSize ( Size value ) {
            _size = BASE_SIZE + value;
            assert ( _size <= MTU );
        }

        ID getId ( ) {
            return _id;
        }

        void setId ( ID id ) {
            _id = id;
        }

        Type getType ( ) {
            return _type;
        }

        void setType ( Type type ) {
            _type = type;
        }
    } ;

    class RegisterRequest : public RegisterMessage
    {
    protected:
    public:

        RegisterRequest ( )
        : RegisterMessage ( RegisterMessage::REGISTER_REQUEST ) { }
    } ;

    class RegisterResponse : public RegisterMessage
    {
    public:
        static const unsigned char BASE_SIZE = sizeof (bool );
    protected:
        bool _isRegistered;
    public:

        RegisterResponse ( )
        : RegisterMessage ( BASE_SIZE, RegisterMessage::REGISTER_RESPONSE ) { }

        bool isRegistered ( ) {
            return _isRegistered;
        }

        void setIsRegistered ( bool value ) {
            _isRegistered = value;
        }
    } ;

    class RegisterObjectRequest : public RegisterMessage
    {
    protected:
        SmartObject * _object;
    public:

        RegisterObjectRequest ( SmartObject * object )
        : RegisterMessage ( strlen ( object->getName ( ) ), RegisterMessage::REGISTER_OBJECT_REQUEST ),
        _object ( object ) { }

        const char * getObjectName ( ) {
            return _object->getName ( );
        }

        SmartObject* getObject ( ) {
            return _object;
        }

        void setObject ( SmartObject * object ) {
            _object = object;
            setSizeAddedWithBaseSize ( strlen ( object->getName ( ) ) );
        }
    } ;

    class RegisterObjectResponse : public RegisterMessage
    {
    protected:
    public:

        RegisterObjectResponse ( )
        : RegisterMessage ( RegisterMessage::REGISTER_OBJECT_RESPONSE ) { }
    } ;

    class RegisterServiceRequest : public RegisterMessage
    {
    protected:
        Service * _service;
    public:

        RegisterServiceRequest ( Service * service )
        : RegisterMessage ( strlen ( service->getName ( ) ), RegisterMessage::REGISTER_SERVICE_REQUEST ),
        _service ( service ) { }

        const char * getServiceName ( ) {
            return _service->getName ( );
        }

        Service* getService ( ) {
            return _service;
        }

        void setService ( Service * service ) {
            _service = service;
            setSizeAddedWithBaseSize ( strlen ( service->getName ( ) ) );
        }
    } ;

    class RegisterServiceResponse : public RegisterMessage
    {
    protected:
    public:

        RegisterServiceResponse ( )
        : RegisterMessage ( RegisterMessage::REGISTER_SERVICE_RESPONSE ) { }
    } ;

    class RegisterParameterRequest : public RegisterMessage
    {
    public:
        typedef Parameter::RegisterIdValue RegisterIdValue;
    protected:
        Parameter * _parameter;
    public:

        RegisterParameterRequest ( Parameter * parameter )
        : RegisterMessage ( RegisterMessage::REGISTER_PARAMETER_REQUEST ),
        _parameter ( parameter ) {
            updateSize ( );
        }

        Parameter* getParameter ( ) {
            return _parameter;
        }

        void setParameter ( Parameter * parameter ) {
            _parameter = parameter;
            updateSize ( );
        }

        const char * getParameterName ( ) {
            return _parameter->getName ( );
        }

        RegisterIdValue getRegisterId ( ) {
            return _parameter->getRegisterId ( );
        }

        bool isReadOnly(){
            return _parameter->isReadOnly();
        }

        ParameterType::Type getType ( ) {
            return _parameter->getType ( );
        }

        const char * getMinValue ( ) {
            return _parameter->getMinValue ( );
        }

        const char * getMaxValue ( ) {
            return _parameter->getMaxValue ( );
        }

    protected:

        void updateSize ( ) {
            Size size = sizeof (ParameterType::Type );
            size += sizeof (RegisterIdValue );
            size += sizeof (bool);

            const char * tmp = _parameter->getMinValue ( );
            size += ( unsigned char ) tmp[0];
            tmp = _parameter->getMaxValue ( );
            size += ( unsigned char ) tmp[0];

            size += strlen ( _parameter->getName ( ) );
            setSizeAddedWithBaseSize ( size );
        }
    } ;

    class RegisterParameterResponse : public RegisterMessage
    {
    protected:
    public:

        RegisterParameterResponse ( )
        : RegisterMessage ( RegisterMessage::REGISTER_PARAMETER_RESPONSE ) { }
    } ;

    class RegisterOptionRequest : public RegisterMessage
    {
    protected:
        const char * _option;
    public:

        RegisterOptionRequest ( const char * option )
        : RegisterMessage ( strlen ( option ), RegisterMessage::REGISTER_OPTION_REQUEST ),
        _option ( option ) { }

        const char * getOption ( ) {
            return _option;
        }

        void setOption ( const char * option ) {
            _option = option;
            setSizeAddedWithBaseSize ( strlen ( option ) );
        }
    } ;

    class RegisterOptionResponse : public RegisterMessage
    {
    protected:
    public:

        RegisterOptionResponse ( )
        : RegisterMessage ( RegisterMessage::REGISTER_OPTION_RESPONSE ) { }
    } ;

    class RegisterEndObjectRequest : public RegisterMessage
    {
    protected:
    public:

        RegisterEndObjectRequest ( )
        : RegisterMessage ( RegisterMessage::REGISTER_END_OBJECT_REQUEST ) { }
    } ;

    class RegisterEndObjectResponse : public RegisterMessage
    {
    protected:
    public:

        RegisterEndObjectResponse ( )
        : RegisterMessage ( RegisterMessage::REGISTER_END_OBJECT_RESPONSE ) { }
    } ;

};

#endif