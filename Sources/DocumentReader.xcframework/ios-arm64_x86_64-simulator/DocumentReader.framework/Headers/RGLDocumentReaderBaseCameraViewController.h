#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <DocumentReader/RGLScenario.h>
#import <DocumentReader/RGLProcessParams.h>
#import <DocumentReader/RGLCornerView.h>
#import <DocumentReader/RGLPreviewView.h>
#import <DocumentReader/RGLMaskView.h>
#import <DocumentReader/RGLActivityIndicator.h>
#import <DocumentReader/RGLDocumentView.h>
#import <DocumentReader/RGLDocumentReaderResults.h>
#import <DocumentReader/RGLImageQualityGroup.h>
#import <DocumentReader/RGLDocumentPosition.h>
#import <DocumentReader/RGLFunctionality.h>

#import <CoreMotion/CoreMotion.h>

#import <RegulaCommon/RegulaCommon.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, RGLCameraScanMode) {
    RGLCameraScanModeContinues,
    RGLCameraScanModeCapture
} NS_SWIFT_NAME(CameraScanMode);

typedef NS_ENUM(NSInteger, RGLTorchModeDevice) {
    RGLTorchModeDeviceClearScreen = 0,
    RGLTorchModeDeviceWhiteScreen  = 1
} NS_SWIFT_NAME(TorchModeDevice);

@class RGLDocumentReaderBaseCameraViewController, RGLDocumentReaderResults;

typedef NS_ENUM(NSInteger, RGLCameraViewControllerAction) {
    RGLCameraViewControllerActionDone,
    RGLCameraViewControllerActionProcess,
    RGLCameraViewControllerActionCancel,
    RGLCameraViewControllerActionMorePagesAvailable,
    RGLCameraViewControllerBadLicense,
    RGLCameraViewControllerActionProcessWhiteFlashLight,
    RGLCameraViewControllerOnlineProcessingError,
    RGLCameraViewControllerOnlineProcessingStarted,
    RGLCameraViewControllerCreateBackendTransactionError,
    RGLCameraViewControllerCameraPermissionDenied
} NS_SWIFT_NAME(CameraViewControllerAction);

typedef void (^RGLCameraViewControllerHandler)(RGLDocumentReaderBaseCameraViewController * _Nullable controller,
                                            RGLCameraViewControllerAction action,
                                            RGLDocumentReaderResults * _Nullable results) NS_SWIFT_NAME(CameraViewControllerHandler);

@protocol RGLDocumentReaderCameraViewControllerDelegate <NSObject>

- (void)handleCameraOpened;
- (BOOL)didMotionControlEnabledInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)didSkipFocusingFramesInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showCaptureButtonInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showChangeFrameSizeButtonInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showSwapCameraButtonInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showTorchButtonInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showCloseButtonInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable AVCaptureSessionPreset )videoSessionPresetInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showLogoInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showHelpAnimationInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)multipageProcessingInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (UIInterfaceOrientationMask)supportedOrientationsInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (void)startNewPageInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showStatusMessagesInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showResultMessagesInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (UIColor *)tintColorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (UIColor *)cameraPreviewBackgroundColorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (UIColor *)resultStatusTextColorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIFont *)resultStatusTextFontInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIColor *)resultStatusBackgroundColorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (UIColor *)cameraFrameDefaultColorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (UIColor *)cameraFrameActiveColorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)cameraFrameBorderWidthInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)cameraFrameWidthOfssetInCameraController:(RGLDocumentReaderBaseCameraViewController * )controller;
- (BOOL)cameraFrameHideInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (UIColor *)statusTextColorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIFont *)statusTextFontInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (UIColor *)statusBackgroundColorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIColor *)activityIndicatorViewColorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIColor *)skipMultipageButtonBackgroundColorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIColor *)skipMultipageButtonTextColorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIFont *)skipMultipageButtonTextFontInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable NSString *)skipMultipageButtonTextInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (RGLCameraFrameShapeType)cameraFrameShapeTypeInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)cornerViewLineLengthInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showNextPageAnimationInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (NSTimeInterval)nextPageAnimationStartDelay:(RGLDocumentReaderBaseCameraViewController *)controller;
- (NSTimeInterval)nextPageAnimationEndDelay:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showMaskViewInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (RGLDocReaderFrame)cameraFrameSizeInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (RGLDocReaderFrame)defaultCameraFrameSizeInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable NSArray<NSNumber *> *)barcodeTypesInCameraController:(RGLDocumentReaderBaseCameraViewController * )controller;
- (AVCaptureDevicePosition)cameraPositionInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)showSkipNextPageButtonInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIImage *)helpAnimationImageInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIImage *)multipageAnimationFrontImageInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIImage *)multipageAnimationBackImageInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)statusPositionMultiplierInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)resultStatusPositionMultiplierInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIImage *)borderBackgroundImageInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)isUseAuthenticatorInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable NSString *)cameraStatusInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)cameraFrameVerticalPositionMultiplier:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)cameraFrameCornerRadius:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)cameraBorderAspectRatioPortrait:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)cameraBorderAspectRatioLandscape:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)isShowCaptureButton:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)torchIsUsed:(RGLDocumentReaderBaseCameraViewController *)controller;
- (NSTimeInterval)showCaptureButtonDelayFromDetect:(RGLDocumentReaderBaseCameraViewController *)controller;
- (NSTimeInterval)showCaptureButtonDelayFromStart:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)shouldStartRecordingOnCapture:(RGLDocumentReaderBaseCameraViewController *)controller;
- (BOOL)shouldStartAutoRecording:(RGLDocumentReaderBaseCameraViewController *)controller;
- (nullable UIImage *)livenessAnimationImageInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)livenessAnimationPositionMultiplierInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (UIViewContentMode)livenessAnimationContentModeInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)previewLayerPositionMultiplierInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)acitivityIndicatorPortraitPositionMultiplierInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;
- (CGFloat)acitivityIndicatorLandscapePositionMultiplierInCameraController:(RGLDocumentReaderBaseCameraViewController *)controller;

@end

@interface RGLDocumentReaderBaseCameraViewController : RGLCBaseViewController

@property(nonatomic, strong, nullable) RGLCameraViewControllerHandler cameraViewControllerHandler;
@property(nonatomic, weak, nullable) id<RGLDocumentReaderCameraViewControllerDelegate> cameraViewControllerDelegate;

@property(nonatomic, assign) BOOL isRecognitionActive;

- (void)notifyCameraPreviewBackgroundColorChanged;
- (void)notifyTintColorChanged;
- (void)notifyResultStatusTextColorChanged;
- (void)notifyResultStatusTextFontChanged;
- (void)notifyCameraFrameDefaultColorChanged;
- (void)notifyCameraFrameActiveColorChanged;
- (void)notifyStatusTextColorChanged;
- (void)notifyStatusTextFontChanged;
- (void)notifyStatusBackgroundColorChanged;
- (void)notifyShowStatusMessagesChanged;
- (void)notifyShowResultStatusMessagesChanged;
- (void)notifyCameraStatusChanged;
- (void)notifyCameraResultStatusChanged;
- (void)notifyCameraFrameShapeTypeChanged;
- (void)notifyMultipageButtonBackgroundColorChanged;
- (void)notifyMultipageButtonTextColorChanged;
- (void)notifyMultipageButtonTextFontChanged;
- (void)notifyMultipageButtonTextChanged;
- (void)notifyCameraFrameBorderWidthChanged;
- (void)notifyActivityIndicatorColorChanged;
- (void)notifyResultStatusBackgroundColorChanged;
- (void)notifyCameraFrameLineLengthChanged;
- (void)notifyCameraFrameOffsetWidthChanged;
- (void)notifyShowBackgroundMaskChanged;
- (void)notifyBackgroundMaskColorChanged;
- (void)notifyBorderBackgroundImageChanged;
- (void)notifyBackgroundMaskAlphaChanged;
- (void)notifyMultipageAnimationFrontImageContentModeChanged;
- (void)notifyMultipageAnimationBackImageContentModeChanged;
- (void)notifyBorderBackgroundImageContentModeChanged;
- (void)notifyMultipageAnimationFrontImageChanged;
- (void)notifyMultipageAnimationBackImageChanged;
- (void)notifyCustomLabelStatusChanged;
- (void)notifyLivenessAnimationImageChanged;
- (void)notifyLivenessAnimationImageContentModeChanged;
- (void)notifyCustomUILayerJSONChanged;

- (void)processParamChanged;
- (void)setHiddenForFlashButton:(BOOL)isHidden;
- (void)setHiddenForCloseButton:(BOOL)isHidden;
- (void)setHiddenForCaptureButton:(BOOL)isHidden;
- (void)setHiddenForSwapCameraButton:(BOOL)isHidden;
- (void)setVideoSessionPreset:(AVCaptureSessionPreset)sessionPreset;
- (void)setVideoZoomFactor:(CGFloat)videoZoomFactor;
- (void)setAVCaptureDevicePosition:(AVCaptureDevicePosition)cameraPosition;
- (void)setShowChangeFrameButton:(BOOL)showChangeFrameButton;
- (void)enableProcessingUI:(BOOL)enable;
- (void)enablePrepareCameraUI:(BOOL)enable;

- (void)closeCameraViewController:(void(^_Nullable)(void))completion;

@end

NS_ASSUME_NONNULL_END
