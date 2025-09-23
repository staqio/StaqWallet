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
#import "RGLDocumentReaderBaseCameraViewController.h"

#import <CoreMotion/CoreMotion.h>

NS_ASSUME_NONNULL_BEGIN

@class RGLDocumentReaderBaseCameraViewController, RGLDocumentReaderResults;
@class RGLDocumentReaderCameraViewControllerDelegate;

NS_SWIFT_NAME(DocumentReaderCameraViewController)
@interface RGLDocumentReaderCameraViewController : RGLDocumentReaderBaseCameraViewController

@property(nonatomic, assign) BOOL resultStatusLocked;

@property(readonly, nonatomic, assign) AVCaptureDevicePosition cameraPosition;
@property(nonatomic, assign) BOOL showHelpPopup;
@property(nonatomic, assign) BOOL helpAnimationShowed;
@property(nonatomic, assign) BOOL showResultMessages;
@property(nonatomic, assign) BOOL showStatusMessages;
@property(nonatomic, assign) BOOL recognizeWasInterrupted;
@property(nonatomic, assign) BOOL skipNextPageRecognition;
@property(nonatomic, assign) double motionRate;
@property(nonatomic, strong, nullable) NSString *cameraStatusString;

@property(nonatomic, strong, nullable) RGLDocumentReaderResults *latestResult;

@property (nonatomic, getter=isCameraControllerPresentedModally) BOOL cameraControllerPresentedModally;

@property(nonatomic, strong, nullable) RGLPreviewView *previewView;
@property(nonatomic, strong, nullable) UIButton *closeButton;
@property(nonatomic, strong, nullable) UIButton *flashButton;
@property(nonatomic, strong, nullable) UIButton *swapCameraButton;
@property(nonatomic, strong, nullable) UIButton *bleButton;
@property(nonatomic, strong, nullable) UIButton *batteryButton;
@property(nonatomic, strong, nullable) UILabel *statusLabel;
@property(nonatomic, strong, nullable) UIView *statusView;
@property(nonatomic, strong, nullable) UIButton *captureButton;
@property(nonatomic, strong, nullable) UIButton *skipMultipageButton;
@property(nonatomic, strong, nullable) UILabel *resultStatusLabel;
@property(nonatomic, strong, nullable) UIView *resultStatusView;
@property(nonatomic, strong, nullable) UIButton *frameSizeButton;
@property(nonatomic, strong, nullable) RGLMaskView *maskView;
@property(nonatomic, strong, nullable) UIImageView *logoImage;
@property(nonatomic, strong, nullable) RGLCornerView *borderView;
@property(nonatomic, strong, nullable) UIView *focusView;
@property(nonatomic, strong, nullable) UILabel *cameraUnavailableLabel;
@property(nonatomic, strong, nullable) RGLActivityIndicator *activityIndicator;
@property(nonatomic, strong, nullable) RGLDocumentView *multipageScaningView;
@property(nonatomic, strong, nullable) RGLDocumentView *helpAnimationView;
@property(nonatomic, strong, nullable) UIImageView *borderPlaceholderImage;
@property(nonatomic, assign) BOOL barcodeEnabled;
@property(nonatomic, assign) BOOL faceEnabled;
@property(nonatomic, assign) RGLCameraScanMode cameraScanMode;
@property(nonatomic, strong, nullable) UILabel *customLabel;

@property(nonatomic, assign) BOOL recognitionIsActive;

@property(nonatomic, assign) RGLDocReaderFrame currentCameraFrame;

- (void)closeTapped:(UIButton *)button;
- (void)flashTapped:(UIButton *)button;
- (void)swapTapped:(UIButton *)button;
- (void)captureButtonTapped:(UIButton *)button;
- (void)skipMultipageTapped:(UIButton *)button;
- (void)changeFrameTapped:(UIButton *)button;
    
@end

NS_ASSUME_NONNULL_END
