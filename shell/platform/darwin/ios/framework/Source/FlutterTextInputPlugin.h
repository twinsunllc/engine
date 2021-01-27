// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SHELL_PLATFORM_IOS_FRAMEWORK_SOURCE_FLUTTERTEXTINPUTPLUGIN_H_
#define SHELL_PLATFORM_IOS_FRAMEWORK_SOURCE_FLUTTERTEXTINPUTPLUGIN_H_

#import <UIKit/UIKit.h>

#include "flutter/shell/platform/darwin/common/framework/Headers/FlutterChannels.h"
#include "flutter/shell/platform/darwin/ios/framework/Source/FlutterTextInputDelegate.h"
#import "flutter/shell/platform/darwin/ios/framework/Source/FlutterViewController_Internal.h"

@interface FlutterTextInputPlugin : NSObject

@property(nonatomic, assign) id<FlutterTextInputDelegate> textInputDelegate;
@property(nonatomic, assign) FlutterViewController* viewController;
- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result;

/**
 * The `UITextInput` implementation used to control text entry.
 *
 * This is used by `AccessibilityBridge` to forward interactions with iOS'
 * accessibility system.
 */
- (UIView<UITextInput>*)textInputView;

@end

/** An indexed position in the buffer of a Flutter text editing widget. */
@interface FlutterTextPosition : UITextPosition

@property(nonatomic, readonly) NSUInteger index;

+ (instancetype)positionWithIndex:(NSUInteger)index;
- (instancetype)initWithIndex:(NSUInteger)index;

@end

/** A range of text in the buffer of a Flutter text editing widget. */
@interface FlutterTextRange : UITextRange <NSCopying>

@property(nonatomic, readonly) NSRange range;

+ (instancetype)rangeWithNSRange:(NSRange)range;

@end

@interface FlutterTextSelectionRect : UITextSelectionRect

@property(nonatomic, readonly) CGRect rect;
@property(nonatomic, readonly) NSWritingDirection writingDirection;
@property(nonatomic, readonly) BOOL containsStart;
@property(nonatomic, readonly) BOOL containsEnd;
@property(nonatomic, readonly) BOOL isVertical;

+ (instancetype)selectionRectWithRectAndInfo:(CGRect)rect
                            writingDirection:(NSWritingDirection)writingDirection
                               containsStart:(BOOL)containsStart
                                 containsEnd:(BOOL)containsEnd
                                  isVertical:(BOOL)isVertical;

- (instancetype)initWithRectAndInfo:(CGRect)rect
                   writingDirection:(NSWritingDirection)writingDirection
                      containsStart:(BOOL)containsStart
                        containsEnd:(BOOL)containsEnd
                         isVertical:(BOOL)isVertical;

@end

#if FLUTTER_RUNTIME_MODE == FLUTTER_RUNTIME_MODE_DEBUG
FLUTTER_EXPORT
#endif
@interface FlutterTextInputView : UIView <UITextInput, UIScribbleInteractionDelegate>

// UITextInput
@property(nonatomic, readonly) NSMutableString* text;
@property(nonatomic, readonly) NSMutableString* markedText;
@property(readwrite, copy) UITextRange* selectedTextRange;
@property(nonatomic, strong) UITextRange* markedTextRange;
@property(nonatomic, copy) NSDictionary* markedTextStyle;
@property(nonatomic, assign) id<UITextInputDelegate> inputDelegate;

// UITextInputTraits
@property(nonatomic) UITextAutocapitalizationType autocapitalizationType;
@property(nonatomic) UITextAutocorrectionType autocorrectionType;
@property(nonatomic) UITextSpellCheckingType spellCheckingType;
@property(nonatomic) BOOL enablesReturnKeyAutomatically;
@property(nonatomic) UIKeyboardAppearance keyboardAppearance;
@property(nonatomic) UIKeyboardType keyboardType;
@property(nonatomic) UIReturnKeyType returnKeyType;
@property(nonatomic, getter=isSecureTextEntry) BOOL secureTextEntry;
@property(nonatomic) UITextSmartQuotesType smartQuotesType API_AVAILABLE(ios(11.0));
@property(nonatomic) UITextSmartDashesType smartDashesType API_AVAILABLE(ios(11.0));
@property(nonatomic, copy) UITextContentType textContentType API_AVAILABLE(ios(10.0));

// UIScribbleInteractionDelegate
- (void)scribbleInteractionWillBeginWriting:(UIScribbleInteraction*)interaction
    API_AVAILABLE(ios(14.0));
- (void)scribbleInteractionDidFinishWriting:(UIScribbleInteraction*)interaction
    API_AVAILABLE(ios(14.0));
- (BOOL)scribbleInteraction:(UIScribbleInteraction*)interaction
      shouldBeginAtLocation:(CGPoint)location API_AVAILABLE(ios(14.0));
- (BOOL)scribbleInteractionShouldDelayFocus:(UIScribbleInteraction*)interaction
    API_AVAILABLE(ios(14.0));

@property(nonatomic, assign) id<FlutterTextInputDelegate> textInputDelegate;
@property(nonatomic, assign) FlutterViewController* viewController;

@end
#endif  // SHELL_PLATFORM_IOS_FRAMEWORK_SOURCE_FLUTTERTEXTINPUTPLUGIN_H_
