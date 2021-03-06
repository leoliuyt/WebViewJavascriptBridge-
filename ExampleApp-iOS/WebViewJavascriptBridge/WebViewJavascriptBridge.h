//
//  WebViewJavascriptBridge.h
//  ExampleApp-iOS
//
//  Created by Marcus Westin on 6/14/13.
//  Copyright (c) 2013 Marcus Westin. All rights reserved.
//

#import <Foundation/Foundation.h>

#define kMessageSeparator     @"__WVJB_MESSAGE_SEPERATOR__"
#define kCustomProtocolScheme @"wvjbscheme"
#define kQueueHasMessage      @"__WVJB_QUEUE_MESSAGE__"

#if TARGET_OS_IPHONE && defined(__IPHONE_5_0) && (__IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_5_0)
    #define WVJB_WEAK_FALLBACK weak
#elif TARGET_OS_MAC && defined(__MAC_10_7) && (__MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_7)
    #define WVJB_WEAK_FALLBACK weak
#else
    #define WVJB_WEAK_FALLBACK unsafe_unretained
#endif

#if defined __MAC_OS_X_VERSION_MAX_ALLOWED
    #import <WebKit/WebKit.h>
    #define WVJB_PLATFORM_OSX
    #define WVJB_WEBVIEW_TYPE WebView
    #define WVJB_WEBVIEW_DELEGATE_TYPE NSObject
#elif defined __IPHONE_OS_VERSION_MAX_ALLOWED
    #define WVJB_PLATFORM_IOS
    #define WVJB_WEBVIEW_TYPE UIWebView
    #define WVJB_WEBVIEW_DELEGATE_TYPE NSObject<UIWebViewDelegate>
#endif

typedef void (^WVJBResponseCallback)(id responseData);
typedef void (^WVJBHandler)(id data, WVJBResponseCallback responseCallback);

@interface WebViewJavascriptBridge : WVJB_WEBVIEW_DELEGATE_TYPE

+ (instancetype)bridgeForWebView:(WVJB_WEBVIEW_TYPE*)webView handler:(WVJBHandler)handler;
+ (instancetype)bridgeForWebView:(WVJB_WEBVIEW_TYPE*)webView webViewDelegate:(WVJB_WEBVIEW_DELEGATE_TYPE*)webViewDelegate handler:(WVJBHandler)handler;
+ (void)enableLogging;
/**
 *  oc调用js
 *
 *  @param message 发送的消息
 */
- (void)send:(id)message;
- (void)send:(id)message responseCallback:(WVJBResponseCallback)responseCallback;
/**
 *  js调用oc
 *  在oc中向js中注册事件 等待在HTML中触发 回调事件
 *
 *  @param handlerName 注册事件名
 *  @param handler     HTML中的事件的回调
 */
- (void)registerHandler:(NSString*)handlerName handler:(WVJBHandler)handler;

/**
 *  oc调用js
 *  在js中向oc注册事件 等待在oc中触发
 *  @param handlerName 注册事件名
 */
- (void)callHandler:(NSString*)handlerName;
- (void)callHandler:(NSString*)handlerName data:(id)data;
- (void)callHandler:(NSString*)handlerName data:(id)data responseCallback:(WVJBResponseCallback)responseCallback;
- (void)reset;

@end
