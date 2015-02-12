/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <array>
#include <algorithm>

//Project Includes
#include "corvusoft/restbed/status_code.h"
#include "corvusoft/restbed/detail/method_impl.h"

//External Includes
#include <corvusoft/framework/string>

//System Namespaces
using std::array;
using std::string;
using std::none_of;
using std::invalid_argument;

//Project Namespaces
using framework::String;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        MethodImpl::MethodImpl( const char* value ) : m_value( String::empty )
        {
            if ( value == nullptr )
            {
                throw StatusCode::METHOD_NOT_ALLOWED;
            }

            setup( string( value ) );
        }
        
        MethodImpl::MethodImpl( const string& value ) : m_value( String::empty )
        {
            setup( value );
        }
        
        MethodImpl::MethodImpl( const MethodImpl& original ) : m_value( original.m_value )
        {
            return;
        }
        
        MethodImpl::~MethodImpl( void )
        {
            return;
        }
        
        string MethodImpl::to_string( void ) const
        {
            return m_value;
        }
        
        bool MethodImpl::operator <( const MethodImpl& value ) const
        {
            return m_value < value.m_value;
        }
        
        bool MethodImpl::operator >( const MethodImpl& value ) const
        {
            return m_value > value.m_value;
        }
        
        bool MethodImpl::operator ==( const MethodImpl& value ) const
        {
            return m_value == value.m_value;
        }
        
        bool MethodImpl::operator !=( const MethodImpl& value ) const
        {
            return m_value not_eq value.m_value;
        }
        
        MethodImpl& MethodImpl::operator =( const MethodImpl& value )
        {
            m_value = value.m_value;
            
            return *this;
        }
        
        void MethodImpl::setup( const string& value )
        {
            const static array< string, 8 > methods = {{
                    "GET",
                    "PUT",
                    "POST",
                    "HEAD",
                    "TRACE",
                    "DELETE",
                    "CONNECT",
                    "OPTIONS"
                }
            };
            
            const string method = String::uppercase( value );
            
            auto validation_failed = none_of( methods.begin( ), methods.end( ), [ &method ] ( const string& value )
            {
                return method == value;
            } );
            
            if ( validation_failed )
            {
                throw StatusCode::METHOD_NOT_ALLOWED;
            }
            
            m_value = method;
        }
    }
}
